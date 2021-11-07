#include <stdafx.h>

#include "port_widget.h"

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
		layout()->setMargin(0);
		layout()->setSpacing(PIN_SPACING);
		for (int i = 0; i < pin_count; i++)
			{
				pin_widget* wdg = new pin_widget(pins_begin++, this);
				m_pin_widgets.push_back(wdg);
				layout()->addWidget(wdg);
			}
	}
} // namespace lcd