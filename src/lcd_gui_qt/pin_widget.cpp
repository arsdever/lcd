#include <stdafx.h>

#include "pin_widget.h"

#include <port.h>
#include <qpainter>
#include <qpaintevent>

namespace lcd
{
	namespace
	{
		static constexpr qreal PIN_RADIUS = 8;
		static constexpr qreal PIN_WEIGHT = 2;
	} // namespace

	pin_widget::pin_widget(pin* p, QWidget* parent) : QWidget(parent), m_underlying_pin(p)
	{
		setFixedSize(QSize(PIN_RADIUS + PIN_WEIGHT, PIN_RADIUS + PIN_WEIGHT));
	}

	void pin_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.translate(PIN_WEIGHT / 2.0f, PIN_WEIGHT / 2.0f);
		painter.setPen(QPen(QColor(201, 174, 36), PIN_WEIGHT));
		painter.setBrush(digital_operation::read(*m_underlying_pin) ? Qt::green : Qt::black);
		painter.drawEllipse(0, 0, PIN_RADIUS - PIN_WEIGHT / 2.0f, PIN_RADIUS - PIN_WEIGHT / 2.0f);
	}
} // namespace lcd
