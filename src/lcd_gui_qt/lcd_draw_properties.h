#pragma once

class QPainter;
class QPaintEvent;

namespace lcd
{
	class i_character_data;

	struct lcd_draw_properties
	{
		using symbol_getter_t = std::function<std::array<char, 8>(size_t x, size_t y)>;

		QPainter*		  painter;
		i_character_data* char_data;
		symbol_getter_t	  symbol_getter;
		size_t			  lcd_width;
		size_t			  lcd_height;
		size_t			  rows;
		size_t			  columns;
		float			  char_width;
		float			  char_height;
		float			  char_hspacing;
		float			  char_vspacing;
		float			  pixel_size;
		float			  pixel_spacing;
	};
} // namespace lcd
