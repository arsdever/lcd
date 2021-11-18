#pragma once

#include <qwidget>

class QLabel;

namespace lcd
{
	class pin;

	class pin_tooltip : public QWidget
	{
	public:
		pin_tooltip(pin* p, QWidget* parent = nullptr);

	protected:
		virtual void paintEvent(QPaintEvent* e) override;

	private:
		pin*	m_pin;
		QLabel* m_pin_index;
		QLabel* m_pin_name;
		QLabel* m_voltage;
	};
} // namespace lcd