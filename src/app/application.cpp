#include "stdafx.h"

#include <scheduler.h>
#include <qt_display.h>

lcd::scheduler g_scheduler{};
size_t g_timing_ratio = 1;
std::atomic<bool> g_exit_flag = false;

int main(int argc, char** argv)
{
	//QApplication app(argc, argv);

//	lcd::qt_display panel(nullptr);
//	lcd::lcd_controller_ptr controller = std::move(std::make_shared<lcd::lcd_controller>());
//	panel.set_controller(controller);
//
////	panel.set_char_at(0, 0, 'a');
////	panel.set_char_at(1, 0, 'b');
////	panel.set_char_at(0, 4, 'c');
////	panel.set_char_at(3, 7, 'd');
////	panel.set_char_at(3, 0, 'e');
////	panel.set_char_at(3, 3, 'f');
////	panel.set_char_at(2, 7, 'g');
////	panel.set_char_at(1, 10, 'h');
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::rs)].set_voltage(5.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data0)].set_voltage(5.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data1)].set_voltage(0.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data2)].set_voltage(0.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data3)].set_voltage(0.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data4)].set_voltage(0.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data5)].set_voltage(5.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data6)].set_voltage(5.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::data7)].set_voltage(0.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::en)].set_voltage(5.0f);
//	controller->m_port.m_pins[static_cast<int>(lcd::lcd_controller::pinout::en)].set_voltage(0.0f);
//	panel.show();


	std::cout << "starting in 3 seconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds{ 3 });

	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));
	g_scheduler.add_task([] {}, std::chrono::microseconds(37));

	std::chrono::time_point last_tick = std::chrono::system_clock::now();
	std::thread scheduler_loop([&last_tick]
		{
			while (!g_exit_flag)
			{
				std::chrono::duration elapsed = std::chrono::system_clock::now() - last_tick;
				last_tick += elapsed;
				elapsed /= g_timing_ratio;
				g_scheduler.tick(elapsed);
			}
		}
	);
//	app.exec();10
	while (true);
	g_exit_flag = true;
	scheduler_loop.join();
}
