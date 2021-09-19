#pragma once

#include <i_character_data.h>
#include <lcd_controller.h>

namespace lcd
{
	extern std::array<std::array<char, 8>, 255> default_font;

	class display : public i_character_data
	{
	public:
		display(size_t width, size_t height);
		virtual ~display() = default;

		virtual void setup_font(std::array<std::array<char, 8>, 255> font);
		virtual std::array<std::array<char, 8>, 255> const& font() const;
		virtual void update();

	public:
		void set_controller(lcd_controller_ptr controller);

	protected:
		virtual char& symbol_at(size_t row, size_t column);
		virtual const char& symbol_at(size_t row, size_t column) const;

#pragma region i_character_data

	public:
		virtual void set_char_at(size_t row, size_t column, char ch) override;
		virtual char get_char_at(size_t row, size_t column) const;

#pragma endregion i_character_data

	protected:
		std::array<std::array<char, 8>, 255> m_font;
		size_t m_width;
		size_t m_height;
		std::vector<char> m_visual;
		lcd_controller_ptr m_controller;
	};
}