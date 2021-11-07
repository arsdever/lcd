#include <stdafx.h>

#include "pin_widget.h"

#include <port.h>
#include <qpainter>
#include <qpaintevent>

namespace lcd
{
	namespace
	{
		static constexpr qreal PIN_RADIUS = 10;
		static constexpr qreal PIN_WEIGHT = 2;
	} // namespace

	pin_widget::pin_widget(pin* p, QWidget* parent) : QWidget(parent), m_underlying_pin(p), m_is_mouse_hover(false)
	{
		setFixedSize(QSize(PIN_RADIUS + PIN_WEIGHT, PIN_RADIUS + PIN_WEIGHT));
	}

	void pin_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		qreal radius = m_is_mouse_hover ? PIN_RADIUS : PIN_RADIUS - 2;
		painter.translate((PIN_WEIGHT + PIN_RADIUS) / 2.0f, (PIN_WEIGHT + PIN_RADIUS) / 2.0f);
		painter.setPen(QPen(QColor(201, 174, 36), PIN_WEIGHT));
		painter.setBrush(digital_operation::read(*m_underlying_pin) ? Qt::green : Qt::black);
		painter.drawEllipse(-radius / 2.0f, -radius / 2.0f, radius, radius);
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
