#include "stdafx.h"
#include "lcd_controller.h"

int main()
{
	lcd::lcd_controller controller;
	//lcd::digital_pin<float>::set_state(&controller.m_port.m_pins[4], false);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::en)].set_voltage(5.f);

	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::rs)].set_voltage(0.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::rw)].set_voltage(0.f);

	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data0)].set_voltage(0.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data1)].set_voltage(5.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data2)].set_voltage(0.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data3)].set_voltage(0.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data4)].set_voltage(5.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data5)].set_voltage(0.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data6)].set_voltage(5.f);
	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data7)].set_voltage(5.f);

	controller.m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::en)].set_voltage(0.f);
}