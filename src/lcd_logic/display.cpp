#include "display.h"

namespace lcd
{
	display::display(size_t width, size_t height)
		: m_width(width)
		, m_height(height)
		, m_font(default_font)
		, m_visual(width* height + 1)
	{}

	void display::setup_font(std::array<std::array<char, 8>, 255> font)
	{
		m_font = font;
	}

	void display::set_char_at(size_t row, size_t column, char ch)
	{
		symbol_at(row, column) = ch;
	}

	char display::char_at(size_t row, size_t column) const
	{
		return symbol_at(row, column);
	}

	void display::update() {}

	char& display::symbol_at(size_t row, size_t column)
	{
		if (row < 0 || row > m_height || column < 0 || column > m_width)
			return *m_visual.rbegin();

		return m_visual[row * m_height + column];
	}

	const char& display::symbol_at(size_t row, size_t column) const
	{
		if (row < 0 || row > m_height || column < 0 || column > m_width)
			return *m_visual.crbegin();

		return m_visual[row * m_height + column];
	}
}
