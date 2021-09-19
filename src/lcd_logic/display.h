#pragma once

namespace lcd
{
	std::array<std::array<char, 8>, 255> default_font = {};

	class display
	{
	public:
		display(size_t width, size_t height);
		virtual ~display() = default;

		virtual void setup_font(std::array<std::array<char, 8>, 255> font);
		virtual void set_char_at(size_t row, size_t column, char ch);
		virtual char char_at(size_t row, size_t column) const;
		virtual void update();

	protected:
		virtual char& symbol_at(size_t row, size_t column);
		virtual const char& symbol_at(size_t row, size_t column) const;

	protected:
		std::array<std::array<char, 8>, 255> m_font;
		size_t m_width;
		size_t m_height;
		std::vector<char> m_visual;
	};
}