#include <stdafx.h>

#include "pin_tooltip.h"

#include "pcb_graphics_settings.h"

#include <pin.h>
#include <qlabel>

namespace lcd
{
	pin_tooltip::pin_tooltip(pin* p, QWidget* parent) : QWidget(parent), m_pin(p)
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlags(Qt::FramelessWindowHint);

		m_pin_index = new QLabel(p->get_name().c_str());
		m_pin_name	= new QLabel(std::to_string(p->get_index()).c_str());
		m_voltage	= new QLabel(std::to_string(p->get_voltage()).c_str());

		setLayout(new QVBoxLayout());
		layout()->addWidget(m_pin_index);
		layout()->addWidget(m_pin_name);
		layout()->addWidget(m_voltage);

		p->register_to_event(pin::event_types_enum::on_voltage_changed,
							 [ this ] { m_voltage->setText(std::to_string(m_pin->get_voltage()).c_str()); });
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