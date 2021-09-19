#pragma once

#include <lcd_draw_properties.h>
#include <i_lcd_drawer.h>

namespace lcd
{
	class lcd_background_drawer : public i_lcd_drawer
	{
	public:
		virtual void draw(lcd_draw_properties config) override;
	};
}
