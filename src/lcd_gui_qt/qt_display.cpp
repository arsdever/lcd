#include "qt_display.h"
#include "lcd_draw_properties.h"
#include "lcd_background_drawer.h"
#include "lcd_content_drawer.h"

#include <qpainter.h>
#include <QPaintEvent>

namespace lcd
{
	qt_display::qt_display(QWidget* parent)
		: QWidget(parent)
		, display(16, 4)
	{
		m_drawers.push_back(std::move(std::make_shared<lcd_background_drawer>()));
		m_drawers.push_back(std::move(std::make_shared<lcd_content_drawer>()));
	}

#pragma region QWidget

	void qt_display::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		for (i_lcd_drawer_ptr drawer : m_drawers)
		{
			painter.save();

			lcd_draw_properties props = {};
			std::memset(&props, 0, sizeof(lcd_draw_properties));
			props.painter = &painter;
			props.lcd_width = e->rect().width();
			props.lcd_height = e->rect().height();
			props.columns = m_width;
			props.rows = m_height;
			props.font = &m_font;
			props.char_data = this;
			props.pixel_size = 3;
			props.pixel_spacing = 1;
			props.char_width = 5;
			props.char_height = 8;
			props.char_hspacing = 4;
			props.char_vspacing = 4;
			drawer->draw(props);

			painter.restore();
		}
	}

#pragma endregion QWidget

#pragma region display

	void qt_display::update()
	{
		QWidget::update();
	}

#pragma endregion display
}
