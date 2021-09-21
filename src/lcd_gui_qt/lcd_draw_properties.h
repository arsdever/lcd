#pragma once

class QPainter;
class QPaintEvent;

namespace lcd
{
	class i_character_data;

	struct lcd_draw_properties
	{
		QPainter* painter;
		i_character_data* char_data;
		std::array<std::array<char, 8>, 255> const* font;
		size_t lcd_width;
		size_t lcd_height;
		size_t rows;
		size_t columns;
		size_t char_width;
		size_t char_height;
		size_t char_hspacing;
		size_t char_vspacing;
		size_t pixel_size;
		size_t pixel_spacing;
	};
}
