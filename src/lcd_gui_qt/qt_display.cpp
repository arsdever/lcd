#include "qt_display.h"

#include "lcd_background_drawer.h"
#include "lcd_content_drawer.h"
#include "lcd_draw_properties.h"

#include <QPaintEvent>
#include <qpainter.h>

namespace lcd
{
	constexpr int	   ce_pixel_size { 3 };
	constexpr int	   ce_pixel_spacing { 1 };
	constexpr int	   ce_char_width { 5 };
	constexpr int	   ce_char_height { 8 };
	constexpr int	   ce_char_hspacing { 4 };
	constexpr int	   ce_char_vspacing { 4 };
	constexpr QMargins ce_margins { 10, 10, 10, 10 };

	qt_display::qt_display(QWidget* parent) : QWidget(parent), display(16, 4)
	{
		m_drawers.push_back(std::move(std::make_shared<lcd_background_drawer>()));
		m_drawers.push_back(std::move(std::make_shared<lcd_content_drawer>()));
	}

#pragma region QWidget

	QSize qt_display::sizeHint() const
	{
		QSize char_size = { ce_char_width * (ce_pixel_size + ce_pixel_spacing) - ce_pixel_spacing,
							ce_char_height * (ce_pixel_size + ce_pixel_spacing) - ce_pixel_spacing };
		return QSize { static_cast<int>(m_width * (char_size.width() + ce_char_hspacing) - ce_char_hspacing),
					   static_cast<int>(m_height * (char_size.height() + ce_char_vspacing) - ce_char_vspacing )} +
			   QSize { ce_margins.left() + ce_margins.right(), ce_margins.top() + ce_margins.bottom() };
	}

	void qt_display::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.translate(ce_margins.left(), ce_margins.top());
		for (i_lcd_drawer_ptr drawer : m_drawers)
			{
				painter.save();

				lcd_draw_properties props = {};
				std::memset(&props, 0, sizeof(lcd_draw_properties));
				props.painter		= &painter;
				props.lcd_width		= e->rect().width();
				props.lcd_height	= e->rect().height();
				props.columns		= m_width;
				props.rows			= m_height;
				props.font			= &m_font;
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

	void qt_display::update() { QWidget::update(); }

#pragma endregion display
} // namespace lcd
