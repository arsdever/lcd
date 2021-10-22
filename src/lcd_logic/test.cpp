#include "stdafx.h"

#include "lcd_controller.h"
#include "scheduler.h"
#include "std_timer.h"

constexpr float g_timing_ratio = 1.f;
lcd::scheduler	g_scheduler;

int main()
{
	lcd::i_timer_ptr tmr = std::make_shared<lcd::std_timer>();
	tmr->set_prescaler(g_timing_ratio);

	g_scheduler.set_timer(tmr);

	lcd::lcd_controller controller;
	// lcd::digital_pin<float>::set_state(&controller.m_port.m_pins[4], false);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(5.f);

	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rs) ].set_voltage(0.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rw) ].set_voltage(0.f);

	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data0) ].set_voltage(0.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data1) ].set_voltage(5.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data2) ].set_voltage(0.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data3) ].set_voltage(0.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data4) ].set_voltage(5.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data5) ].set_voltage(0.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data6) ].set_voltage(5.f);
	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data7) ].set_voltage(5.f);

	controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(0.f);
}