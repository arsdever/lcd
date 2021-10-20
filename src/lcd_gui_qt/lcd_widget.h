#pragma once

#include <qwidget.h>
#include <lcd_controller.h>

namespace lcd
{
	class lcd_widget : public QWidget, lcd_controller
	{
		Q_OBJECT

	public:
		lcd_widget(QWidget* parent = nullptr);

		virtual void port_updated_callback(pinout p) override;
		virtual void execute(execution_data const& data) override;
	};
}