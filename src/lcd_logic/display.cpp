#include "display.h"

#include "lcd_controller.h"

#include <lcd_assert.h>

namespace lcd
{
	display::display(size_t width, size_t height) : m_width(width), m_height(height), m_visual(width * height + 1) { }

	void display::update() { }

	char& display::symbol_at(size_t row, size_t column)
	{
		if (row < 0 || row > m_height || column < 0 || column > m_width)
			return m_controller->symbol_at_ddram(0x00);

		return m_controller->symbol_at_ddram(row % 2 * 0x40 + row / 2 * m_width + column);
	}

	const char& display::symbol_at(size_t row, size_t column) const
	{
		if (m_controller->lines() == lcd_controller::display_lines_mode_enum::single_line && row % 2)
			{
				return ' ';
			}

		uint8_t addr = address_of_symbol(row, column);
		if (addr == 0xff)
			{
				lcd_assert(false,
						   std::string("Invalid address returned for display symbol at: ") + std::to_string(column) +
							   " " + std::to_string(row));

				return ' ';
			}

		return m_controller->symbol_at_ddram(addr);
	}

	uint8_t display::address_of_symbol(size_t row, size_t column) const
	{
		if (row < 0 || row > m_height || column < 0 || column > m_width)
			{
				lcd_assert(false,
						   std::string("The requested symbol is out of the lcd space: ") + std::to_string(column) +
							   " " + std::to_string(row));

				return uint8_t(0xff);
			}

		if (m_controller->lines() == lcd_controller::display_lines_mode_enum::single_line)
			{
				// TODO: the display scroll is not encounted
				return static_cast<uint8_t>(row / 2 * m_width + column);
			}
		else
			{
				return static_cast<uint8_t>(row % 2 * 0x40 +
											(row / 2 * m_width + column + m_controller->scroll_size()) % (2 * m_width));
			}
	}

	void display::set_controller(lcd_controller_ptr controller)
	{
		m_controller = controller;
		controller->register_for_updates([ = ]() { update(); });
	}

#pragma region i_character_data

	void display::set_char_at(size_t row, size_t column, char ch)
	{
		symbol_at(row, column) = ch;
		update();
	}

	char display::get_char_at(size_t row, size_t column) const { return symbol_at(row, column); }

	std::array<char, 8> display::get_symbol_at(size_t row, size_t column) const
	{
		if (m_controller->cursor_state() == lcd_controller::cursor_mode_enum::box &&
			address_of_symbol(row, column) == m_controller->cursor_position())
			{
				return {
					char(0xff), char(0xff), char(0xff), char(0xff), char(0xff), char(0xff), char(0xff), char(0xff)
				};
			}
		else
			{
				char				symb = symbol_at(row, column);
				void*				source;
				std::array<char, 8> result;

				symb < 8 ? source = m_controller->m_cgram.data() + 8 * symb
						 : source = m_controller->m_cgrom.data() + 8 * (symb - 8);

				std::memcpy(result.data(), source, 8);
				if (m_controller->cursor_state() == lcd_controller::cursor_mode_enum::line &&
					address_of_symbol(row, column) == m_controller->cursor_position())
					result.data()[ 7 ] = char(0xff);

				return result;
			}
	}

#pragma endregion i_character_data
} // namespace lcd
