#include "stdafx.h"

#include "lcd_controller.h"

#include "scheduler.h"

#include <lcd_assert.h>
#include <logger.h>

extern lcd::scheduler g_scheduler;

namespace lcd
{
	namespace
	{
		void init_default_font(char* dest)
		{
			static constexpr char data[] = {
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x0e,
				0x0f, 0x0e, 0x0c, 0x08, 0x00, 0x02, 0x06, 0x0e, 0x1e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x09, 0x12, 0x1b,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x09, 0x12, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x1f, 0x00, 0x04,
				0x0e, 0x1f, 0x00, 0x1f, 0x0e, 0x04, 0x00, 0x1f, 0x0e, 0x04, 0x00, 0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x0e,
				0x00, 0x00, 0x01, 0x01, 0x05, 0x09, 0x1f, 0x08, 0x04, 0x00, 0x04, 0x0e, 0x15, 0x04, 0x04, 0x04, 0x04,
				0x00, 0x04, 0x04, 0x04, 0x04, 0x15, 0x0e, 0x04, 0x00, 0x00, 0x04, 0x02, 0x1f, 0x02, 0x04, 0x00, 0x00,
				0x00, 0x04, 0x08, 0x1f, 0x08, 0x04, 0x00, 0x00, 0x02, 0x04, 0x08, 0x04, 0x02, 0x00, 0x1f, 0x00, 0x08,
				0x04, 0x02, 0x04, 0x08, 0x00, 0x1f, 0x00, 0x00, 0x04, 0x04, 0x0e, 0x0e, 0x1f, 0x00, 0x00, 0x00, 0x1f,
				0x0e, 0x0e, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04,
				0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x0a, 0x1f, 0x0a,
				0x1f, 0x0a, 0x0a, 0x00, 0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04, 0x00, 0x18, 0x19, 0x02, 0x04, 0x08,
				0x13, 0x03, 0x00, 0x0c, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0d, 0x00, 0x0c, 0x04, 0x08, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08,
				0x00, 0x00, 0x04, 0x15, 0x0e, 0x15, 0x04, 0x00, 0x00, 0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x0e, 0x11,
				0x13, 0x15, 0x19, 0x11, 0x0e, 0x00, 0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e, 0x00, 0x0e, 0x11, 0x01,
				0x02, 0x04, 0x08, 0x1f, 0x00, 0x1f, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0e, 0x00, 0x02, 0x06, 0x0a, 0x12,
				0x1f, 0x02, 0x02, 0x00, 0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e, 0x00, 0x06, 0x08, 0x10, 0x1e, 0x11,
				0x11, 0x0e, 0x00, 0x1f, 0x11, 0x01, 0x02, 0x04, 0x04, 0x04, 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11,
				0x0e, 0x00, 0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00,
				0x00, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x04, 0x08, 0x00, 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00,
				0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00, 0x0e,
				0x11, 0x01, 0x02, 0x04, 0x00, 0x04, 0x00, 0x0e, 0x11, 0x01, 0x0d, 0x15, 0x15, 0x0e, 0x00, 0x04, 0x0a,
				0x11, 0x11, 0x1f, 0x11, 0x11, 0x00, 0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e, 0x00, 0x0e, 0x11, 0x10,
				0x10, 0x10, 0x11, 0x0e, 0x00, 0x1c, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1c, 0x00, 0x1f, 0x10, 0x10, 0x1e,
				0x10, 0x10, 0x1f, 0x00, 0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x10, 0x00, 0x0e, 0x11, 0x10, 0x17, 0x11,
				0x11, 0x0f, 0x00, 0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11, 0x00, 0x0e, 0x04, 0x04, 0x04, 0x04, 0x04,
				0x0e, 0x00, 0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c, 0x00, 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11,
				0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x00, 0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00,
				0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, 0x00, 0x1e,
				0x11, 0x11, 0x1e, 0x10, 0x10, 0x10, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0d, 0x00, 0x1e, 0x11,
				0x11, 0x1e, 0x14, 0x12, 0x11, 0x00, 0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e, 0x00, 0x1f, 0x04, 0x04,
				0x04, 0x04, 0x04, 0x04, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, 0x00, 0x11, 0x11, 0x11, 0x11,
				0x11, 0x0a, 0x04, 0x00, 0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0a, 0x00, 0x11, 0x11, 0x0a, 0x04, 0x0a,
				0x11, 0x11, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x00, 0x1f, 0x01, 0x02, 0x04, 0x08, 0x10,
				0x1f, 0x00, 0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e, 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00,
				0x00, 0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e, 0x00, 0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f, 0x00, 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1e, 0x00, 0x00, 0x00,
				0x0e, 0x10, 0x10, 0x11, 0x0e, 0x00, 0x01, 0x01, 0x0d, 0x13, 0x11, 0x11, 0x0f, 0x00, 0x00, 0x00, 0x0e,
				0x11, 0x1f, 0x10, 0x0e, 0x00, 0x06, 0x09, 0x08, 0x1c, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x11,
				0x0f, 0x01, 0x0e, 0x00, 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00, 0x04, 0x00, 0x04, 0x0c, 0x04,
				0x04, 0x0e, 0x00, 0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0c, 0x00, 0x10, 0x10, 0x12, 0x14, 0x18, 0x14,
				0x12, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e, 0x00, 0x00, 0x00, 0x1a, 0x15, 0x15, 0x15, 0x15,
				0x00, 0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e, 0x00,
				0x00, 0x00, 0x1e, 0x11, 0x1e, 0x10, 0x10, 0x00, 0x00, 0x00, 0x0d, 0x13, 0x0f, 0x01, 0x01, 0x00, 0x00,
				0x00, 0x16, 0x19, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x0e, 0x10, 0x0e, 0x01, 0x1e, 0x00, 0x08, 0x08,
				0x1c, 0x08, 0x08, 0x09, 0x06, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d, 0x00, 0x00, 0x00, 0x11,
				0x11, 0x11, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0a, 0x00, 0x00, 0x00, 0x11, 0x0a,
				0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x11, 0x11, 0x0f, 0x01, 0x0e, 0x00, 0x00, 0x00, 0x1f, 0x02, 0x04,
				0x08, 0x1f, 0x00, 0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
				0x04, 0x00, 0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x12, 0x00, 0x00,
				0x00, 0x04, 0x0a, 0x11, 0x11, 0x11, 0x1f, 0x00, 0x00, 0x1f, 0x11, 0x10, 0x1e, 0x11, 0x11, 0x1e, 0x0f,
				0x05, 0x05, 0x09, 0x11, 0x1f, 0x11, 0x11, 0x00, 0x15, 0x15, 0x15, 0x0e, 0x15, 0x15, 0x15, 0x00, 0x1e,
				0x01, 0x01, 0x06, 0x01, 0x01, 0x1e, 0x00, 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x0a, 0x04, 0x11,
				0x11, 0x13, 0x15, 0x19, 0x11, 0x00, 0x0f, 0x05, 0x05, 0x05, 0x05, 0x15, 0x09, 0x00, 0x1f, 0x11, 0x11,
				0x11, 0x11, 0x11, 0x11, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04, 0x08, 0x10, 0x00, 0x11, 0x11, 0x11, 0x11,
				0x11, 0x1f, 0x01, 0x00, 0x11, 0x11, 0x11, 0x0f, 0x01, 0x01, 0x01, 0x00, 0x00, 0x15, 0x15, 0x15, 0x15,
				0x15, 0x1f, 0x00, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1f, 0x01, 0x00, 0x18, 0x08, 0x08, 0x0e, 0x09, 0x09,
				0x0e, 0x00, 0x11, 0x11, 0x11, 0x19, 0x15, 0x15, 0x19, 0x00, 0x0e, 0x11, 0x05, 0x0b, 0x01, 0x11, 0x0e,
				0x00, 0x00, 0x00, 0x09, 0x15, 0x12, 0x12, 0x0d, 0x00, 0x04, 0x06, 0x05, 0x05, 0x04, 0x1c, 0x1c, 0x00,
				0x1f, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x13, 0x00, 0x3f,
				0x20, 0x10, 0x08, 0x10, 0x20, 0x3f, 0x00, 0x00, 0x00, 0x0f, 0x12, 0x12, 0x12, 0x0c, 0x06, 0x05, 0x07,
				0x05, 0x05, 0x1d, 0x1b, 0x03, 0x00, 0x00, 0x01, 0x0e, 0x14, 0x04, 0x04, 0x02, 0x00, 0x04, 0x0e, 0x0e,
				0x0e, 0x1f, 0x04, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x0e, 0x11, 0x11,
				0x11, 0x0a, 0x1b, 0x00, 0x06, 0x09, 0x04, 0x0a, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x0b, 0x15, 0x1a,
				0x00, 0x00, 0x00, 0x00, 0x0a, 0x1f, 0x1f, 0x1f, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x0e, 0x10, 0x0c, 0x11,
				0x0e, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11
			};
			std::memcpy(dest, data, sizeof(data));
		};
	} // namespace

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
		: m_interface_type { interface_type_enum::undefined }, m_on_update_cb { nullptr }, m_vscroll { 0 },
		  m_hscroll { 0 }, m_cursor_show { false }, m_cursor_move_direction { cursor_direction_enum::increment },
		  m_insert { false }, m_blink { false }, m_busy { false }, m_display_on { false }, m_lines { false },
		  m_font { false }, m_scroll_direction { false }, m_address_mode { address_mode::ddram },
		  m_cgram_address_counter { 0 }, m_cgram { 0 }, m_ddram_address_counter { 0 }, m_ddram { 0 }
	{
		init_default_font(m_cgrom.data());
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

		execution_data data { rw_mode, rs_mode, value_from_bus() };
		execute(data);
	}

	void lcd_controller::execute(execution_data const& data)
	{
		logger::info(std::string("execution: ") + std::to_string(static_cast<int>(data.rs_mode)) + " " +
					 std::to_string(static_cast<int>(data.rw_mode)) + " " +
					 std::to_string(static_cast<int>(data.data)));

		bool			   is_rs_mode	= static_cast<bool>(data.rs_mode);
		bool			   is_rw_mode	= static_cast<bool>(data.rw_mode);
		command_types_enum command_type = command_types_enum::clear;

		// Handling read_busy_flag_and_address
		// This should be done separately because the instruction doesn't care
		// about the busy state of te controller and doesn't contribute into it.
		if (!is_rs_mode && is_rw_mode)
			{
				switch (m_address_mode)
					{
					case address_mode::cgram: value_to_bus(m_cgram_address_counter); break;
					case address_mode::ddram: value_to_bus(m_ddram_address_counter); break;
					}

				digital_operation::write(m_port.m_pins[ static_cast<int>(pinout::data7) ], is_busy());
				return;
			}

		if (m_busy)
			{
				logger::warn("The controller is in the busy mode, but a new command is incoming");
				return;
			}

		m_busy = true;

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
				lcd_assert(false, "read_busy_flag_and_address is handled separately: this code should not be executed");
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
			case command_types_enum::display_on_off_control:
				{
					instruction_impl = [ & ] { m_display_on = false; };
					break;
				}
			case command_types_enum::cursor_or_display_shift: break;
			case command_types_enum::function_set: break;
			case command_types_enum::set_cgram_address: break;
			case command_types_enum::set_ddram_address: break;
			case command_types_enum::read_busy_flag_and_address: break;
			case command_types_enum::write_data_to_cg_or_ddram:
				{
					instruction_impl = [ &, data ] {
						switch (m_address_mode)
							{
							case address_mode::cgram:
								{
									m_cgram[ m_cgram_address_counter ] = data.data;
									m_cgram_address_counter +=
										m_cursor_move_direction == cursor_direction_enum::increment ? 1 : -1;

									if (m_cgram_address_counter >= m_cgram.size())
										m_cgram_address_counter = 0;
									else if (m_cgram_address_counter < 0)
										m_cgram_address_counter = m_cgram.size() - 1;

									break;
								}
							case address_mode::ddram:
								{
									m_ddram[ m_ddram_address_counter ] = data.data;
									if (m_cursor_move_direction == cursor_direction_enum::increment)
										{
											++m_ddram_address_counter;

											if (++m_hscroll >= 40)
												{
													m_hscroll -= 40;
												}
										}
									else
										{
											--m_ddram_address_counter;
											if (--m_hscroll < 0)
												{
													m_hscroll += 40;
												}
										}

									if (m_ddram_address_counter >= m_ddram.size())
										m_ddram_address_counter = 0;
									else if (m_ddram_address_counter < 0)
										m_ddram_address_counter = m_ddram.size() - 1;

									break;
								}
							}
					};
					break;
				}
			case command_types_enum::read_data_from_cg_or_ddram:
				{
					instruction_impl = [ & ] {
						switch (m_address_mode)
							{
							case address_mode::cgram:
								{
									value_to_bus(m_cgram[ m_cgram_address_counter ]);

									m_cgram_address_counter +=
										m_cursor_move_direction == cursor_direction_enum::increment ? 1 : -1;

									if (m_cgram_address_counter >= m_cgram.size())
										m_cgram_address_counter = 0;
									else if (m_cgram_address_counter < 0)
										m_cgram_address_counter = m_cgram.size() - 1;

									break;
								}
							case address_mode::ddram:
								{
									value_to_bus(m_ddram[ m_ddram_address_counter ]);
									m_ddram_address_counter +=
										m_cursor_move_direction == cursor_direction_enum::increment ? 1 : -1;

									if (m_ddram_address_counter >= m_ddram.size())
										m_ddram_address_counter = 0;
									else if (m_ddram_address_counter < 0)
										m_ddram_address_counter = m_ddram.size() - 1;

									break;
								}
							}
					};
					break;
				}
			}

		if (!instruction_impl)
			{
				lcd_assert(false, "The instruction leads to an empty functionality");
				return;
			}

		scheduler::task_t executor = [ &busy = m_busy, &updater = m_on_update_cb, instruction_impl ] {
			instruction_impl();
			busy = false;

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

	void lcd_controller::value_to_bus(uint8_t value)
	{
		for (int i = static_cast<int>(pinout::data0); i <= static_cast<int>(pinout::data7); ++i)
			{
				digital_operation::write(m_port.m_pins[ i ], value & 1);
				value >>= 1;
			}
	}

	uint8_t lcd_controller::value_from_bus()
	{
		uint8_t value = 0;
		for (int i = static_cast<int>(pinout::data7); i >= static_cast<int>(pinout::data0); --i)
			{
				value <<= 1;
				value |= static_cast<uint8_t>(digital_operation::read(m_port.m_pins[ i ]));
			}
		return value;
	}
} // namespace lcd