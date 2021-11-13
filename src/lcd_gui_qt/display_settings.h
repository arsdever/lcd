#pragma once

namespace lcd
{
	struct display_settings
	{
		using symbol_getter_t = std::function<std::array<char, 8>(size_t x, size_t y)>;

		symbol_getter_t get_symbol;
		size_t			rows;
		size_t			columns;
		float			char_width;
		float			char_height;
		float			char_hspacing;
		float			char_vspacing;
		float			pixel_size;
		float			pixel_spacing;
	};
} // namespace lcd