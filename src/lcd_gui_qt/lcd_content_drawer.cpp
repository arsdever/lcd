#include "lcd_content_drawer.h"

#include <i_character_data.h>
#include <qpainter.h>

namespace lcd
{
	void lcd_content_drawer::draw(lcd_draw_properties props)
	{
		QPainter& painter = *props.painter;
		float	  chw	  = (props.pixel_size + props.pixel_spacing) * (props.char_width - 1) + props.pixel_size;
		float	  chh	  = (props.pixel_size + props.pixel_spacing) * (props.char_height - 1) + props.pixel_size;

		for (size_t chy = 0; chy < props.rows; ++chy)
			{
				painter.save();

				for (size_t chx = 0; chx < props.columns; ++chx)
					{
						painter.save();

						std::array<char, 8> character = props.symbol_getter(chy, chx);
						for (char chrow : character)
							{
								painter.save();

								for (int i = props.char_width - 1; i >= 0; --i)
									{
										painter.fillRect(0,
														 0,
														 props.pixel_size,
														 props.pixel_size,
														 (chrow & (1 << i)) ? QColor("#3c412c") : QColor("#7b9f31"));
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
} // namespace lcd
