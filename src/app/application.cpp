#include "stdafx.h"

#include <qapplication.h>
#include <qt_display.h>
#include <scheduler.h>
#include <std_timer.h>

// smaller value will decrease the speed of the simulation
constexpr double g_timing_ratio = .001f;
lcd::scheduler	 g_scheduler { []() -> std::unique_ptr<lcd::i_timer> {
	std::unique_ptr<lcd::i_timer>tmr = std::make_unique<lcd::std_timer>();
	tmr->set_prescaler(g_timing_ratio);
	return std::move(tmr);
} };
std::atomic<bool> g_exit_flag = false;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	lcd::qt_display			panel(nullptr);
	lcd::lcd_controller_ptr controller = std::move(std::make_shared<lcd::lcd_controller>());
	panel.set_controller(controller);

	// panel.set_char_at(0, 0, 'a');
	// panel.set_char_at(1, 0, 'b');
	// panel.set_char_at(0, 4, 'c');
	// panel.set_char_at(3, 7, 'd');
	// panel.set_char_at(3, 0, 'e');
	// panel.set_char_at(3, 3, 'f');
	// panel.set_char_at(2, 7, 'g');
	// panel.set_char_at(1, 10, 'h');
	panel.show();

	std::chrono::time_point last_tick = std::chrono::system_clock::now();
	std::thread([ = ]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rw) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rs) ].set_voltage(5.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data0) ].set_voltage(5.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data1) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data2) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data3) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data4) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data5) ].set_voltage(5.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data6) ].set_voltage(5.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data7) ].set_voltage(0.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(5.0f);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(0.0f);
	}).detach();
	std::thread scheduler_loop([ &last_tick ] {
		g_scheduler.start();
		while (!g_exit_flag)
			{
				// std::chrono::duration elapsed = std::chrono::system_clock::now() - last_tick;
				// last_tick += elapsed;
				// std::chrono::duration<double> doubleElapsed = elapsed;
				// doubleElapsed /= g_timing_ratio;
				g_scheduler.tick();
			}
	});
	int result	= app.exec();
	g_exit_flag = true;
	scheduler_loop.join();
	return result;
}
