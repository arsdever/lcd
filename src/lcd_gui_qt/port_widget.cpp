#include <stdafx.h>

#include "port_widget.h"

#include "pcb_graphics_settings.h"
#include "pin_widget.h"

#include <port.h>

namespace lcd
{
	namespace
	{
		static constexpr int PIN_SPACING = 2;
	} // namespace

	port_widget::port_widget(pin* pins_begin, int pin_count, QWidget* parent) : QWidget(parent)
	{
		setLayout(new QHBoxLayout());
		layout()->setContentsMargins(2, 2, 2, 15);
		layout()->setSpacing(PIN_SPACING);
		setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		for (int i = 0; i < pin_count; i++)
			{
				pin_widget* wdg = new pin_widget(pins_begin++, this);
				m_pin_widgets.push_back(wdg);
				layout()->addWidget(wdg);
			}
	}

	void port_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.fillRect(e->rect(), g_pcb_graphics_settings.light_color);
		pin_widget* wdg = m_pin_widgets.front();
		for (pin_widget* wdg : m_pin_widgets)
			{
				QPointF center = wdg->pos() + QPoint(wdg->width() / 2.0f, wdg->height() / 2.0f);

				// draw the hole clearance region
				painter.setBrush(g_pcb_graphics_settings.dark_color);
				painter.setPen(Qt::NoPen);
				painter.drawEllipse(center, wdg->width() / 2.0 + 2, wdg->height() / 2.0 + 2);
				painter.drawRect(
					center.x() - wdg->width() / 2.0 - 1, center.y(), wdg->width() + 2, e->rect().height() - center.y());
				painter.setBrush(Qt::NoBrush);

				float trace_expansion_amount = 10;
				float trace_width			 = g_pcb_graphics_settings.trace_width;

				// draw the pass through hole clearance region
				painter.setPen(Qt::NoPen);
				painter.setBrush(g_pcb_graphics_settings.dark_color);
				painter.drawEllipse(center + QPointF(0, trace_expansion_amount + trace_width),
									trace_width / 2.0 + 2,
									trace_width / 2.0 + 2);

				// draw the pass through hole
				painter.setPen(QPen(g_pcb_graphics_settings.light_color, trace_width / 2.0));
				painter.drawEllipse(
					center + QPointF(0, trace_expansion_amount + trace_width), trace_width / 2.0, trace_width / 2.0);

				// draw the trace
				painter.setPen(QPen(g_pcb_graphics_settings.light_color, trace_width));
				painter.drawLine(center, QPoint(center.x(), center.y() + trace_expansion_amount));
			}
	}
} // namespace lcd