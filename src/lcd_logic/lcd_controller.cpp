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
		: m_interface_type { interface_type_enum::eight_pin_interface },
		  m_display_lines_mode { display_lines_mode_enum::single_line },
		  m_font(fonts_enum::five_eight), m_on_update_cb { nullptr }, m_scroll { 0 }, m_cursor_show { false },
		  m_move_direction { move_direction_enum::increment }, m_insert { false }, m_blink { false }, m_busy { false },
		  m_display_on { false }, m_address_mode_enum { address_mode_enum::ddram }, m_cgram_address_counter { 0 }, m_cgram { 0 },
		  m_ddram_address_counter { 0 }, m_ddram { 0 }
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
				switch (m_address_mode_enum)
					{
					case address_mode_enum::cgram: value_to_bus(m_cgram_address_counter); break;
					case address_mode_enum::ddram: value_to_bus(m_ddram_address_counter); break;
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
								break;
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
						m_scroll				= 0;
					};
					break;
				}
			case command_types_enum::entry_mode_set:
				{
					instruction_impl = [ & ] {
						bool dir		 = digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data1) ]);
						m_move_direction = static_cast<move_direction_enum>(dir);
					};
					break;
				}
			case command_types_enum::display_on_off_control:
				{
					instruction_impl = [ & ] { m_display_on = false; };
					break;
				}
			case command_types_enum::cursor_or_display_shift:
				{
					instruction_impl = [ & ] {
						move_direction_enum dir =
							digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data2) ])
								? move_direction_enum::right
								: move_direction_enum::left;
						cursor_shift(dir);
						if (digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data3) ]))
							display_shift(dir);
					};
					break;
				}
			case command_types_enum::function_set:
				{
					instruction_impl = [ & ] {
						m_interface_type	 = digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data4) ])
												   ? interface_type_enum::eight_pin_interface
												   : interface_type_enum::four_pin_interface;
						m_display_lines_mode = digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data3) ])
												   ? display_lines_mode_enum::double_line
												   : display_lines_mode_enum::single_line;
						if (m_display_lines_mode == display_lines_mode_enum::double_line)
							m_font = fonts_enum::five_eight;
						else
							m_font = digital_operation::read(m_port.m_pins[ static_cast<int>(pinout::data2) ])
										 ? fonts_enum::five_eight
										 : fonts_enum::five_ten;
					};
					break;
				}
			case command_types_enum::set_cgram_address:
				{
					instruction_impl = [ & ] {
						m_address_mode_enum		= address_mode_enum::cgram;
						m_cgram_address_counter = value_from_bus() & 0x3f;
					};
					break;
				}
			case command_types_enum::set_ddram_address:
				{
					instruction_impl = [ & ] {
						m_address_mode_enum		= address_mode_enum::ddram;
						m_ddram_address_counter = value_from_bus() & 0x7f;
					};
					break;
				}
			case command_types_enum::read_busy_flag_and_address: break;
			case command_types_enum::write_data_to_cg_or_ddram:
				{
					instruction_impl = [ &, data ] {
						switch (m_address_mode_enum)
							{
							case address_mode_enum::cgram:
								{
									m_cgram[ m_cgram_address_counter ] = data.data;
									cgram_shift(m_move_direction);
									break;
								}
							case address_mode_enum::ddram:
								{
									m_ddram[ m_ddram_address_counter ] = data.data;
									cursor_shift(m_move_direction);
									// TODO: the display should be shifted only if the flag is set
									// display_shift(m_move_direction);
									break;
								}
							}
					};
					break;
				}
			case command_types_enum::read_data_from_cg_or_ddram:
				{
					instruction_impl = [ & ] {
						switch (m_address_mode_enum)
							{
							case address_mode_enum::cgram:
								{
									value_to_bus(m_cgram[ m_cgram_address_counter ]);
									cgram_shift(m_move_direction);
									break;
								}
							case address_mode_enum::ddram:
								{
									value_to_bus(m_ddram[ m_ddram_address_counter ]);
									cursor_shift(m_move_direction);
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

	void lcd_controller::cgram_shift(move_direction_enum dir)
	{
		m_cgram_address_counter += (dir == move_direction_enum::left) ? -1 : 1;
		if (m_cgram_address_counter >= m_cgram.size())
			m_cgram_address_counter = 0;
		else if (m_cgram_address_counter < 0)
			m_cgram_address_counter = m_cgram.size() - 1;
	}

	void lcd_controller::cursor_shift(move_direction_enum dir)
	{
		m_ddram_address_counter += (dir == move_direction_enum::left) ? -1 : 1;
		if (m_ddram_address_counter >= m_ddram.size())
			m_ddram_address_counter = 0;
		else if (m_ddram_address_counter < 0)
			m_ddram_address_counter = m_ddram.size() - 1;
	}

	void lcd_controller::display_shift(move_direction_enum dir)
	{
		m_scroll += (dir == move_direction_enum::left) ? -1 : 1;
	}

	char& lcd_controller::symbol_at_ddram(size_t address) { return m_ddram[ address ]; }

	const char& lcd_controller::symbol_at_ddram(size_t address) const { return m_ddram[ address ]; }

	bool lcd_controller::is_busy() const { return m_busy; }

	lcd_controller::interface_type_enum lcd_controller::interface_type() const { return m_interface_type; }

	lcd_controller::display_lines_mode_enum lcd_controller::lines() const { return m_display_lines_mode; }

	lcd_controller::fonts_enum lcd_controller::font() const { return m_font; }

	size_t lcd_controller::cursor_position() const { return m_ddram_address_counter; }

	int8_t lcd_controller::scroll_size() const { return m_scroll; }

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