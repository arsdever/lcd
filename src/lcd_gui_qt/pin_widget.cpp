#include <stdafx.h>

#include "pin_widget.h"

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

		setFixedSize(QSize((hole_radius + hole_width) * 2, (hole_radius + hole_width) * 2));
	}

	void pin_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		float hole_radius = g_pcb_graphics_settings.through_hole_radius;
		float hole_width  = g_pcb_graphics_settings.through_hole_width;

		qreal radius = m_is_mouse_hover ? hole_radius : hole_radius - 2;
		painter.translate(hole_width + hole_radius, hole_width + hole_radius);
		painter.setPen(QPen(g_pcb_graphics_settings.gold_color, hole_width));
		painter.setBrush(digital_operation::read(*m_underlying_pin) ? Qt::green : Qt::black);
		painter.drawEllipse(-radius, -radius, radius * 2, radius * 2);
	}

	void pin_widget::enterEvent(QEvent* e)
	{
		m_is_mouse_hover = true;
		update();
	}

	void pin_widget::leaveEvent(QEvent* e)
	{
		m_is_mouse_hover = false;
		update();
	}
} // namespace lcd
