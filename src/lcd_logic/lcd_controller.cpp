#include "stdafx.h"

#include "lcd_controller.h"

#include "scheduler.h"

#include <assert.h>
#include <logger.h>

extern lcd::scheduler g_scheduler;

namespace lcd
{
	std::unordered_map<lcd_controller::command_types_enum, std::chrono::nanoseconds>
		lcd_controller::s_execution_time_map = {
			{ lcd_controller::command_types_enum::clear, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::return_home, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::entry_mode_set, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::display_on_off_control, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::cursor_or_display_shift, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::function_set, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::set_cgram_address, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::set_ddram_address, std::chrono::microseconds { 37 } },
			{ lcd_controller::command_types_enum::read_busy_flag_and_address, std::chrono::microseconds { 37 } },
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
			std::bind(&lcd_controller::port_updated_callback, this, pinout::en));
	}

	void lcd_controller::register_for_updates(on_update_delegate callback) { m_on_update_cb = callback; }

	void lcd_controller::port_updated_callback(pinout p)
	{
		read_write_mode_enum rw_mode = read_write_mode_enum::write;
		registers_mode_enum	 rs_mode = registers_mode_enum::instruction;

		if (p == pinout::en)
			{
				if (digital_read::get(m_port.m_pins[ static_cast<int>(pinout::rw) ]))
					{
						rw_mode = read_write_mode_enum::read;
					}

				if (digital_read::get(m_port.m_pins[ static_cast<int>(pinout::rs) ]))
					{
						rs_mode = registers_mode_enum::data;
					}

				uint8_t value = 0;
				for (int i = static_cast<int>(pinout::data7); i >= static_cast<int>(pinout::data0); --i)
					{
						value <<= 1;
						value |= static_cast<uint8_t>(digital_read::get(m_port.m_pins[ i ]));
					}

				switch (rs_mode)
					{
					case registers_mode_enum::instruction: handle_command(value); break;
					case registers_mode_enum::data: handle_data(value); break;
					}
			}
	}

	void lcd_controller::handle_command(uint8_t command)
	{
		logger::info(std::string("Recieved command: ") + std::to_string(static_cast<int>(command)));

		if (digital_read::get(m_port.m_pins[ static_cast<int>(pinout::rw) ]))
			{
				// TODO: Return busy flag and address counter
				return;
			}

		if (m_on_update_cb)
			m_on_update_cb();

		for (int i = 7; i >= 0; --i)
			{
				if (command & (1 << i))
					{
						handle_command(static_cast<command_types_enum>(i));
					}
			}
	}

	void lcd_controller::handle_command(command_types_enum command_type)
	{
		if (m_busy)
			{
				logger::warn(std::string("The controller is in the busy mode, but a new command is incoming: ") +
							  std::to_string(static_cast<int>(command_type)));
				return;
			}
		m_busy = true;
		g_scheduler.add_task([ &busy = m_busy ] { busy = false; }, s_execution_time_map[ command_type ]);

		switch (command_type)
			{
			case command_types_enum::clear:
				std::memset(m_ddram.data(), ' ', m_ddram.size());
				m_ddram_address_counter = 0x00;
				break;
			case command_types_enum::return_home:
				m_ddram_address_counter = 0x00;
				m_vscroll				= 0;
				m_hscroll				= 0;
				break;
			case command_types_enum::entry_mode_set:
				{
					bool dir				= digital_read::get(m_port.m_pins[ static_cast<int>(pinout::data1) ]);
					m_cursor_move_direction = static_cast<cursor_direction_enum>(dir);
					break;
				}
			case command_types_enum::display_on_off_control: break;
			case command_types_enum::cursor_or_display_shift: break;
			case command_types_enum::function_set: break;
			case command_types_enum::set_cgram_address: break;
			case command_types_enum::set_ddram_address: break;
			}
	}

	void lcd_controller::handle_data(uint8_t data)
	{
		m_ddram[ 0 ] = data;
		m_on_update_cb();
		logger::info(std::string("Recieved data: ") + std::to_string(static_cast<int>(data)));
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
} // namespace lcd