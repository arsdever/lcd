#include "lcd_background_drawer.h"

#include <qpainter.h>
#include <QPaintEvent>

namespace lcd
{
	void lcd_background_drawer::draw(lcd_draw_properties props)
	{
		QPainter& painter = *props.painter;

		painter.fillRect(0, 0, props.lcd_width, props.lcd_height, QColor("#87ad34"));
	}
}
