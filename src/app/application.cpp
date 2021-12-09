#include "stdafx.h"

#include "app_main_window.h"

#include <logger.h>
#include <logging/log_widget.h>
#include <pcb_graphics_settings.h>
#include <qapplication.h>
#include <qt_display.h>
#include <scheduler.h>
#include <step_timer.h>

// smaller value will decrease the speed of the simulation
// 1s = 100us
constexpr double	  g_timing_ratio = 10.f;
extern lcd::scheduler g_scheduler;

namespace lcd
{
	pcb_graphics_settings g_pcb_graphics_settings { QColor(24, 79, 58),
													QColor(34, 143, 85),
													QColor(201, 174, 36),
													QColor(201, 174, 36),
													QColor(135, 173, 51),
													QColor(50, 68, 16),
													QColor(200, 230, 89, 32),
													QColor(24, 31, 9),
													3,
													2,
													4,
													2 };
}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	lcd::i_timer_ptr tmr = std::make_shared<lcd::step_timer>();
	tmr->set_prescaler(g_timing_ratio);

	lcd::qt_display*		panel = new lcd::qt_display {};
	lcd::log_widget			log_wdg;
	lcd::app_main_window	window(60.0f, tmr);
	lcd::lcd_controller_ptr controller = std::move(std::make_shared<lcd::lcd_controller>());
	window.on_contrast_slider([ = ](float value) {
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::v0) ].set_voltage(value * 5.0);
	});
	window.on_brightness_slider([ = ](float value) {
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::anode) ].set_voltage(value * 5.0);
		controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::catode) ].set_voltage(0.0f);
	});
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

	std::thread([ = ]() {
		lcd::scheduler::task_id_t idx =
			g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 1); }, {});
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001100); },
								   std::chrono::milliseconds(160),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00111000); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);

		std::string text = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean "
						   "commodo ligula eget "
						   "dolor. Aenean massa. Cum sociis natoque pen";

		for (char c : text)
			{
				idx = g_scheduler.add_task([ instruction, controller, c ] { instruction(*controller, 1, 0, c); },
										   std::chrono::milliseconds(4),
										   true,
										   idx);
			}

		idx = g_scheduler.add_task([] {}, std::chrono::milliseconds(100), true, idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00110000); },
								   std::chrono::milliseconds(100),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00111000); },
								   std::chrono::milliseconds(100),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00000001); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00111000); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b01001000); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);

		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00001110); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00011011); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00010001); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00010001); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00011111); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00011111); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00011111); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 1, 0, 0b00011111); },
								   std::chrono::milliseconds(4),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00011100); },
								   std::chrono::seconds(1),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00011000); },
								   std::chrono::seconds(1),
								   true,
								   idx);
		idx = g_scheduler.add_task([] {}, std::chrono::seconds(1), true, idx);
		for (int i = 0; i < 256; ++i)
			{
				idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00011000); },
										   std::chrono::milliseconds(4),
										   true,
										   idx);
			}
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00000001); },
								   std::chrono::seconds(1),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001111); },
								   std::chrono::milliseconds(160),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001111); },
								   std::chrono::milliseconds(160),
								   true,
								   idx);
		std::string short_text = "Short text";
		for (char c : short_text)
			{
				idx = g_scheduler.add_task([ instruction, controller, c ] { instruction(*controller, 1, 0, c); },
										   std::chrono::milliseconds(100),
										   true,
										   idx);
			}
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001110); },
								   std::chrono::seconds(1),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001100); },
								   std::chrono::seconds(1),
								   true,
								   idx);
		idx = g_scheduler.add_task([ instruction, controller ] { instruction(*controller, 0, 0, 0b00001101); },
								   std::chrono::seconds(1),
								   true,
								   idx);
	}).detach();
	panel->show();
	log_wdg.show();
	int result = app.exec();
	return result;
}
