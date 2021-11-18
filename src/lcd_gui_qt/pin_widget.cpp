#include <stdafx.h>

#include "pin_widget.h"
#include "pin_tooltip.h"

#include <pcb_graphics_settings.h>
#include <port.h>
#include <qlabel>
#include <qpainter>
#include <qpaintevent>

namespace lcd
{
	pin_widget::pin_widget(pin* p, QWidget* parent) : QWidget(parent), m_underlying_pin(p), m_is_mouse_hover(false)
	{
		float hole_radius = g_pcb_graphics_settings.through_hole_radius;
		float hole_width  = g_pcb_graphics_settings.through_hole_width;

		m_tooltip = new pin_tooltip(p);

		setContentsMargins(QMargins(0, 0, 0, 0));
		setFixedSize(QSize((hole_radius + hole_width) * 2, (hole_radius + hole_width) * 2));
	}

	void pin_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		float hole_width = g_pcb_graphics_settings.through_hole_width;

		painter.setPen(QPen(g_pcb_graphics_settings.gold_color, hole_width));
		painter.setBrush(digital_operation::read(*m_underlying_pin) ? Qt::green : Qt::black);
		QRect canvas_rect = e->rect();
		canvas_rect.adjust(hole_width / 2.0, hole_width / 2.0, -hole_width / 2.0, -hole_width / 2.0);

		if (!m_is_mouse_hover)
			canvas_rect.adjust(1, 1, -1, -1);

		painter.drawEllipse(canvas_rect);
	}

	void pin_widget::enterEvent(QEvent* e)
	{
		m_is_mouse_hover = true;
		m_tooltip->show();
		m_tooltip->move(QCursor::pos() + QPoint(- m_tooltip->width() / 2.0, 5));
		update();
	}

	void pin_widget::leaveEvent(QEvent* e)
	{
		m_is_mouse_hover = false;
		m_tooltip->hide();
		update();
	}
} // namespace lcd
