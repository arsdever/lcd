#pragma once

#include <qwidget>

namespace lcd
{
	class pin;

	class pin_widget : public QWidget
	{
		Q_OBJECT

	public:
		pin_widget(pin* p, QWidget* = nullptr);

	protected:
		virtual void paintEvent(QPaintEvent* e) override;
		virtual void enterEvent(QEvent* e) override;
		virtual void leaveEvent(QEvent* e) override;

	private:
		pin* m_underlying_pin;
		bool m_is_mouse_hover;
	};
} // namespace lcd