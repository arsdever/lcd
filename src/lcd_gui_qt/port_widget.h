#pragma once

#include <qwidget>

namespace lcd
{
	class pin;
	class pin_widget;

	class port_widget : public QWidget
	{
	public:
		port_widget(pin* pins_begin, int pin_count, QWidget* parent = nullptr);

	private:
		std::vector<pin_widget*> m_pin_widgets;
	};
} // namespace lcd