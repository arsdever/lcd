#include "qt_display.h"

#include "lcd_background_drawer.h"
#include "lcd_content_drawer.h"
#include "lcd_draw_properties.h"
#include "port_widget.h"

#include <QPaintEvent>
#include <qpainter.h>

namespace lcd
{
	constexpr float	   ce_pixel_size { 3 };
	constexpr float	   ce_pixel_spacing { .4f };
	constexpr float	   ce_char_width { 5 };
	constexpr float	   ce_char_height { 8 };
	constexpr float	   ce_char_hspacing { 6 };
	constexpr float	   ce_char_vspacing { 6 };
	constexpr QMargins ce_padding { 0, 0, 0, 0 };

	qt_display::qt_display(QWidget* parent) : QWidget(parent), display(16, 4)
	{
		m_drawers.push_back(std::move(std::make_shared<lcd_background_drawer>()));
		m_drawers.push_back(std::move(std::make_shared<lcd_content_drawer>()));
		on_controller_changed([ = ] {
			m_port_widget =
				new port_widget(m_controller->m_port.m_pins.data(), m_controller->m_port.m_pins.size(), this);
			m_port_widget->move(0, 0);
		});
	}

#pragma region QWidget

	QSize qt_display::minimumSizeHint() const
	{
		QSizeF char_size = { ce_char_width * (ce_pixel_size + ce_pixel_spacing) - ce_pixel_spacing,
							 ce_char_height * (ce_pixel_size + ce_pixel_spacing) - ce_pixel_spacing };
		QSizeF result	 = QSizeF { m_width * (char_size.width() + ce_char_hspacing) - ce_char_hspacing,
									m_height * (char_size.height() + ce_char_vspacing) - ce_char_vspacing } +
						QSizeF { ce_padding.left() + ce_padding.right(), ce_padding.top() + ce_padding.bottom() };
		return QSize(result.width(), result.height() + m_port_widget->height());
	}

	void qt_display::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::RenderHint::HighQualityAntialiasing, true);
		for (i_lcd_drawer_ptr drawer : m_drawers)
			{
				painter.save();

				lcd_draw_properties props = {};
				std::memset(&props, 0, sizeof(lcd_draw_properties));

				props.painter	 = &painter;
				props.lcd_width	 = e->rect().width();
				props.lcd_height = e->rect().height();
				props.columns	 = m_width;
				props.rows		 = m_height;
				props.symbol_getter =
					std::bind(&qt_display::get_symbol_at, this, std::placeholders::_1, std::placeholders::_2);
				props.char_data		= this;
				props.pixel_size	= ce_pixel_size;
				props.pixel_spacing = ce_pixel_spacing;
				props.char_width	= ce_char_width;
				props.char_height	= ce_char_height;
				props.char_hspacing = ce_char_hspacing;
				props.char_vspacing = ce_char_vspacing;
				drawer->draw(props);

				painter.restore();
			}

		QWidget::paintEvent(e);
	}

#pragma endregion QWidget

#pragma region display

	void qt_display::update(update_reason_enum reason)
	{
		m_port_widget->update();
		QWidget::update();
	}

#pragma endregion display
} // namespace lcd
