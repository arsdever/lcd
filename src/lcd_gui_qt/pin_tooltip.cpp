#include <stdafx.h>

#include "pin_tooltip.h"

#include "pcb_graphics_settings.h"

#include <port.h>
#include <qlabel>

namespace lcd
{
	pin_tooltip::pin_tooltip(pin* p, QWidget* parent) : QWidget(parent), m_pin(p)
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlags(Qt::FramelessWindowHint);

		m_pin_index = new QLabel("INDEX");
		m_pin_name	= new QLabel("NAME");
		m_voltage	= new QLabel("VOLTAGE");

		setLayout(new QVBoxLayout());
		layout()->addWidget(m_pin_index);
		layout()->addWidget(m_pin_name);
		layout()->addWidget(m_voltage);
	}

	void pin_tooltip::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.save();
		painter.setPen(QPen(g_pcb_graphics_settings.dark_color, 2));
		painter.setBrush(g_pcb_graphics_settings.light_color);
		painter.drawRoundRect(e->rect().adjusted(1, 1, -1, -1), 10, 10);
	}
} // namespace lcd