#include "stdafx.h"

#include "lcd_controller.h"

namespace lcd
{
	lcd_controller::lcd_controller()
		: m_interface_type{ interface_type_enum::undefined }
	{
		m_port.m_pins[static_cast<int>(pinout::en)].on_edge_down(std::bind(&lcd_controller::port_updated_callback, this, pinout::en));
	}

	void lcd_controller::port_updated_callback(pinout p)
	{
		read_write_mode_enum rw_mode = read_write_mode_enum::write;
		registers_mode_enum rs_mode = registers_mode_enum::instruction;

		if (p == pinout::en)
		{
			if (digital_read::get(m_port.m_pins[static_cast<int>(pinout::rw)]))
			{
				rw_mode = read_write_mode_enum::read;
			}

			if (digital_read::get(m_port.m_pins[static_cast<int>(pinout::rs)]))
			{
				rs_mode = registers_mode_enum::data;
			}

			uint8_t value = 0;
			for (int i = static_cast<int>(pinout::data7); i >= static_cast<int>(pinout::data0); --i)
			{
				value <<= 1;
				value |= digital_read::get(m_port.m_pins[i]);
			}

			switch (rs_mode)
			{
			case registers_mode_enum::instruction:
				handle_command(value);
				break;
			case registers_mode_enum::data:
				handle_data(value);
				break;
			}
		}
	}

	void lcd_controller::handle_command(uint8_t command)
	{
		std::cout << "Recieved command: " << static_cast<int>(command) << std::endl;
	}
	
	void lcd_controller::handle_data(uint8_t data)
	{
		std::cout << "Recieved data: " << static_cast<int>(data) << std::endl;
	}
}