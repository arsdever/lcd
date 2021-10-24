#pragma once

namespace lcd
{
	class i_character_data
	{
	public:
		virtual ~i_character_data() = default;

		virtual void set_char_at(size_t row, size_t column, char character) = 0;
		virtual char get_char_at(size_t row, size_t column) const = 0;

		virtual std::array<char, 8> get_symbol_at(size_t row, size_t column) const = 0;
	};
}
