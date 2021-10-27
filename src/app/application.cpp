#include "stdafx.h"

#include "app_main_window.h"

#include <qapplication.h>
#include <qt_display.h>
#include <scheduler.h>
#include <std_timer.h>

// smaller value will decrease the speed of the simulation
// 1s = 100us
constexpr double  g_timing_ratio = .01f;
lcd::scheduler	  g_scheduler;
std::atomic<bool> g_exit_flag = false;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	lcd::i_timer_ptr tmr = std::make_shared<lcd::std_timer>();
	tmr->set_prescaler(g_timing_ratio);

	g_scheduler.set_timer(tmr);

	lcd::qt_display*		panel = new lcd::qt_display {};
	lcd::app_main_window	window(60.0f, tmr, panel);
	lcd::lcd_controller_ptr controller = std::move(std::make_shared<lcd::lcd_controller>());
	panel->set_controller(controller);

	// panel.set_char_at(0, 0, 'a');
	// panel.set_char_at(1, 0, 'b');
	// panel.set_char_at(0, 4, 'c');
	// panel.set_char_at(3, 7, 'd');
	// panel.set_char_at(3, 0, 'e');
	// panel.set_char_at(3, 3, 'f');
	// panel.set_char_at(2, 7, 'g');
	// panel.set_char_at(1, 10, 'h');
	window.show();

	auto instruction = [](lcd::lcd_controller& controller, bool rs, bool rw, uint8_t byte) {
		controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rw) ].set_voltage(rw ? 5.0f : 0.0f);
		controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rs) ].set_voltage(rs ? 5.0f : 0.0f);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data0) ],
									  byte & 1);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data1) ],
									  byte & 2);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data2) ],
									  byte & 4);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data3) ],
									  byte & 8);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data4) ],
									  byte & 16);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data5) ],
									  byte & 32);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data6) ],
									  byte & 64);
		lcd::digital_operation::write(controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data7) ],
									  byte & 128);
		controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(5.0f);
		controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(0.0f);
	};

	std::chrono::time_point last_tick = std::chrono::system_clock::now();
	std::thread([ = ]() {
		instruction(*controller, 0, 0, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(160));
		instruction(*controller, 0, 0, 0b00001111);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 0, 0, 0b00111000);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));

		std::string text = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget "
						   "dolor. Aenean massa. Cum sociis natoque pen";

		for (char c : text)
			{
				instruction(*controller, 1, 0, c);
				std::this_thread::sleep_for(std::chrono::milliseconds(4));
			}

		std::this_thread::sleep_for(std::chrono::seconds(1)); // show for a second
		instruction(*controller, 0, 0, 0b00110000);
		std::this_thread::sleep_for(std::chrono::seconds(1)); // set 1 line mode and show a second
		instruction(*controller, 0, 0, 0b00111000);
		std::this_thread::sleep_for(std::chrono::milliseconds(4)); // switch back to 2 line mode
		instruction(*controller, 1, 0, 0b00000001);
		std::this_thread::sleep_for(std::chrono::seconds(1)); // show the 0x01 character element
		instruction(*controller, 0, 0, 0b00111000);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 0, 0, 0b01001000); // set cgram 0x08 (0x01 character)
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00001110); // draw the character
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00011011);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00010001);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00010001);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00011111);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00011111);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00011111);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 1, 0, 0b00011111);
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
		instruction(*controller, 0, 0, 0b00011100);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		instruction(*controller, 0, 0, 0b00011000);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		for (int i = 0; i < 256; ++i)
			{
				instruction(*controller, 0, 0, 0b00011000);
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
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
