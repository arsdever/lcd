#pragma once

namespace lcd
{
	struct lcd_draw_properties;

	class i_lcd_drawer;
	using i_lcd_drawer_ptr = std::shared_ptr<i_lcd_drawer>;
	using i_lcd_drawer_wptr = std::weak_ptr<i_lcd_drawer>;

	class i_lcd_drawer
	{
	public:
		virtual ~i_lcd_drawer() = default;
		virtual void draw(lcd_draw_properties config) = 0;
	};
}
