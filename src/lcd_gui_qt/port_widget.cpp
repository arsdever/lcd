#include <stdafx.h>

#include "port_widget.h"

#include <qpainter>
#include <qpaintevent>

namespace lcd
{
	namespace
	{
		static constexpr int PIN_RADIUS	 = 8;
		static constexpr int PIN_SPACING = 3;
	} // namespace

	port_widget::port_widget(pin* pins_begin, int pin_count, QWidget* parent)
		: QWidget(parent), m_pins_begin_iterator(pins_begin), m_pin_count(pin_count)
	{
	}

	QSize port_widget::sizeHint() const
	{
		return QSize(m_pin_count * (PIN_RADIUS + PIN_SPACING) - PIN_SPACING, PIN_RADIUS);
	}

	void port_widget::paintEvent(QPaintEvent* evt)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		pin*	 it = m_pins_begin_iterator;
		for (int i = 0; i < m_pin_count; ++i, ++it)
			{
				painter.setPen(QPen(QColor(201, 174, 36), 3));
				painter.setBrush(digital_operation::read(*it) ? Qt::green : Qt::black);
				painter.drawEllipse(1.5, 1.5, PIN_RADIUS - 1.5, PIN_RADIUS - 1.5);
				painter.translate(PIN_RADIUS + PIN_SPACING, 0);
			}
	}
} // namespace lcd