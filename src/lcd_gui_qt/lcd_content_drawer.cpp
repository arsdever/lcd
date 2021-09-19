#include "lcd_content_drawer.h"

#include <qpainter.h>
#include <i_character_data.h>

namespace lcd
{
	void lcd_content_drawer::draw(lcd_draw_properties props)
	{
		QPainter& painter = *props.painter;
		size_t chw = (props.pixel_size + props.pixel_spacing) * props.char_width + props.pixel_size;
		size_t chh = (props.pixel_size + props.pixel_spacing) * props.char_height + props.pixel_size;

		for (size_t chy = 0; chy < props.rows; ++chy)
		{
			painter.save();

			for (size_t chx = 0; chx < props.columns; ++chx)
			{
				painter.save();

				std::array<char, 8> character = (*props.font)[props.char_data->get_char_at(chy, chx)];
				for (char chrow : character)
				{
					painter.save();

					for (int i = props.char_width - 1; i >= 0; --i)
					{
						painter.fillRect(0, 0, props.pixel_size, props.pixel_size, (chrow & (1 << i)) ? QColor("3c412c") : QColor("#a8c64e"));
						painter.translate(props.pixel_size + props.pixel_spacing, 0);

					}

					painter.restore();
					painter.translate(0, props.pixel_size + props.pixel_spacing);
				}

				painter.restore();
				painter.translate(chw + props.char_hspacing, 0);
			}

			painter.restore();
			painter.translate(0, chh + props.char_vspacing);
		}
	}
}
