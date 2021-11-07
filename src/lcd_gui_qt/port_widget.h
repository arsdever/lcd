#pragma once

#include <port.h>
#include <qwidget>

namespace lcd
{
	class port_widget : public QWidget
	{
	public:
		port_widget(pin* pins_begin, int pin_count, QWidget* parent = nullptr);

	private:
		virtual QSize sizeHint() const override;
		virtual void paintEvent(QPaintEvent* evt) override;

	private:
		pin* m_pins_begin_iterator;
		int	 m_pin_count;
	};
} // namespace lcd