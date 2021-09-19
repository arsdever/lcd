#include "lcd_widget.h"

namespace lcd
{
	lcd_widget::lcd_widget(QWidget* parent)
		: QWidget(parent)
	{}

	void lcd_widget::port_updated_callback(pinout p) 
	{
	}

	void lcd_widget::handle_command(uint8_t command)
	{
	}

	void lcd_widget::handle_data(uint8_t data) 
	{
	}
}
