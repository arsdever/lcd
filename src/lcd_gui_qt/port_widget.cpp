#include <stdafx.h>

#include "port_widget.h"

#include "pcb_graphics_settings.h"
#include "pin_widget.h"

#include <port.h>

namespace lcd
{
	namespace
	{
		static constexpr int PIN_SPACING = 5;
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
				QRect pin_rect = wdg->rect().adjusted(-2, -2, 2, 2).translated(wdg->pos());
				painter.drawEllipse(pin_rect);

				float trace_expansion_amount = 15;
				float trace_width			 = g_pcb_graphics_settings.trace_width;

				// draw the pass through hole clearance region
				painter.setPen(Qt::NoPen);
				painter.setBrush(g_pcb_graphics_settings.dark_color);
				painter.drawEllipse(
					center + QPointF(0, trace_expansion_amount), trace_width / 2.0 + 3, trace_width / 2.0 + 3);

				painter.setPen(QPen(g_pcb_graphics_settings.dark_color, 2));
				painter.setBrush(g_pcb_graphics_settings.light_color);
				QRectF trace_rect = QRectF(center, QSizeF(trace_width, trace_expansion_amount));
				trace_rect.translate(-trace_width / 2.0, 0);
				painter.drawRect(trace_rect);
				painter.setBrush(Qt::NoBrush);

				// draw the pass through hole
				painter.setPen(QPen(g_pcb_graphics_settings.light_color, trace_width / 2.0));
				painter.drawEllipse(center + QPointF(0, trace_expansion_amount), trace_width / 2.0, trace_width / 2.0);
			}
	}
} // namespace lcd