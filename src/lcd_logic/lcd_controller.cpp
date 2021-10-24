#include "stdafx.h"

#include "lcd_controller.h"

#include "scheduler.h"

#include <lcd_assert.h>
#include <logger.h>

extern lcd::scheduler g_scheduler;

namespace lcd
{
	std::unordered_map<lcd_controller::command_types_enum, std::chrono::nanoseconds>
		lcd_controller::s_execution_time_map = {
			{ lcd_controller::command_types_enum::clear, std::chrono::microseconds { 1520 } },
			{ lcd_controller::command_types_enum::return_home, std::chrono::microseconds { 1520 } },
			{ lcd_controller::command_types_enum::entry_mode_set, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::display_on_off_control, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::cursor_or_display_shift, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::function_set, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::set_cgram_address, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::set_ddram_address, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::read_busy_flag_and_address, std::chrono::microseconds { 0 } },
			{ lcd_controller::command_types_enum::write_data_to_cg_or_ddram, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::read_data_from_cg_or_ddram, std::chrono::microseconds { 37 } },
		};

	lcd_controller::lcd_controller()
		: m_interface_type { interface_type_enum::undefined }, m_vscroll { 0 }, m_hscroll { 0 },
		  m_cursor_show { false }, m_cursor_move_direction { cursor_direction_enum::decrement }, m_insert { false },
		  m_blink { false }, m_busy { false }, m_display_on { false }, m_lines { false }, m_font { false },
		  m_scroll_direction { false }, m_ddram { 0 }
	{
		m_port.m_pins[ static_cast<int>(pinout::en) ].on_edge_down(
			std::bind(&lcd_controller::on_enable_falling_edge, this));
	}

	void lcd_controller::register_for_updates(on_update_delegate callback) { m_on_update_cb = callback; }

	void lcd_controller::port_updated_callback(pinout p) { }

	void lcd_controller::on_enable_falling_edge()
	{
		read_write_mode_enum rw_mode =
			static_cast<read_write_mode_enum>(digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::rw) ]));
		registers_mode_enum rs_mode =
			static_cast<registers_mode_enum>(digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::rs) ]));

		uint8_t value = 0;
		for (int i = static_cast<int>(pinout::data7); i >= static_cast<int>(pinout::data0); --i)
			{
				value <<= 1;
				value |= static_cast<uint8_t>(digital_operation::read(m_port.m_pins[ i ]));
			}

		execution_data data { rw_mode, rs_mode, value };
		execute(data);
	}

	void lcd_controller::execute(execution_data const& data)
	{
		logger::info(std::string("execution: ") + std::to_string(static_cast<int>(data.rs_mode)) + " " +
					 std::to_string(static_cast<int>(data.rw_mode)) + " " +
					 std::to_string(static_cast<int>(data.data)));

		if (m_busy)
			{
				logger::warn("The controller is in the busy mode, but a new command is incoming");
				return;
			}

		m_busy = true;

		bool			   is_rs_mode	= static_cast<bool>(data.rs_mode);
		bool			   is_rw_mode	= static_cast<bool>(data.rw_mode);
		command_types_enum command_type = command_types_enum::clear;

		if (is_rs_mode && is_rw_mode)
			{
				command_type = command_types_enum::read_data_from_cg_or_ddram;
			}
		else if (is_rs_mode && !is_rw_mode)
			{
				command_type = command_types_enum::write_data_to_cg_or_ddram;
			}
		else if (!is_rs_mode && is_rw_mode)
			{
				command_type = command_types_enum::read_busy_flag_and_address;
			}
		else
			{
				for (int i = 7; i >= 0; --i)
					{
						if (data.data & (1 << i))
							{
								command_type = static_cast<command_types_enum>(i);
							}
					}
			}

		scheduler::task_t instruction_impl;

		switch (command_type)
			{
			case command_types_enum::clear:
				{
					instruction_impl = [ & ] {
						m_busy = false;
						std::memset(m_ddram.data(), ' ', m_ddram.size());
						m_ddram_address_counter = 0x00;
					};
					break;
				}
				break;
			case command_types_enum::return_home:
				{
					instruction_impl = [ & ] {
						m_ddram_address_counter = 0x00;
						m_vscroll				= 0;
						m_hscroll				= 0;
					};
					break;
				}
			case command_types_enum::entry_mode_set:
				{
					instruction_impl = [ & ] {
						bool dir = digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data1) ]);
						m_cursor_move_direction = static_cast<cursor_direction_enum>(dir);
					};
					break;
				}
			case command_types_enum::display_on_off_control: break;
			case command_types_enum::cursor_or_display_shift: break;
			case command_types_enum::function_set: break;
			case command_types_enum::set_cgram_address: break;
			case command_types_enum::set_ddram_address: break;
			case command_types_enum::read_busy_flag_and_address: break;
			case command_types_enum::write_data_to_cg_or_ddram:
				{
					instruction_impl = [ &, data ] { m_ddram[ 0 ] = data.data; };
					break;
				}
			case command_types_enum::read_data_from_cg_or_ddram: break;
			}

		if (!instruction_impl)
			{
				lcd_assert(false, "The instruction leads to an empty functionality");
				return;
			}

		scheduler::task_t executor = [ &updater = m_on_update_cb, instruction_impl ] {
			instruction_impl();

			if (updater != nullptr)
				updater();
		};
		g_scheduler.add_task(executor, s_execution_time_map[ command_type ]);
	}

	char& lcd_controller::symbol_at_ddram(size_t address)
	{
		assert(address >= 0x00 && address < 0x28 || address >= 0x40 && address < 0x68);
		if (address > 0x27)
			address -= 40;

		return m_ddram[ address ];
	}

	const char& lcd_controller::symbol_at_ddram(size_t address) const
	{
		assert(address >= 0x00 && address < 0x28 || address >= 0x40 && address < 0x68);
		if (address > 0x27)
			address -= 40;

		return m_ddram[ address ];
	}

	bool lcd_controller::is_busy() const { return m_busy; }
} // namespace lcd