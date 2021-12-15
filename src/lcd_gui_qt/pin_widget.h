#pragma once

#include <lcd_gui_qt_prototypes.h>
#include <lcd_logic_prototypes.h>

namespace lcd
{
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
		pin*		 m_underlying_pin;
		bool		 m_is_mouse_hover;
		pin_tooltip* m_tooltip;
	};
} // namespace lcd