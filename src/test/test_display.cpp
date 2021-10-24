#include <stdafx.h>
#define BOOST_TEST_MODULE "lcd_logic unit tests"
#include <boost/test/unit_test.hpp>
#include <lcd_controller.h>
#include <logger.h>
#include <scheduler.h>
#include <std_timer.h>

lcd::scheduler g_scheduler {};

namespace lcd
{
	class test_framework
	{
	public:
		inline test_framework() : m_exit_flag { false }
		{
			logger::set_log_level(logger::log_level::error);
			m_timer = std::make_shared<std_timer>();
			g_scheduler.set_timer(m_timer);
		}

		inline ~test_framework() { stop(); }

		inline void set_prescaler(double prescaler) { m_timer->set_prescaler(prescaler); }

		inline void start()
		{
			m_scheduler_thread = std::thread([ &exit_flag = m_exit_flag ] {
				g_scheduler.start();
				while (!exit_flag)
					{
						g_scheduler.tick();
					}
			});
		}

		inline void stop()
		{
			if (m_scheduler_thread.joinable())
				{
					m_exit_flag = true;
					m_scheduler_thread.join();
				}
		}

		inline void command(bool rw, uint8_t byte)
		{
			m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rw) ].set_voltage(rw ? 5.0f
																										   : 0.0f);
			m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rs) ].set_voltage(5.0f);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data0) ],
									 byte & 1);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data1) ],
									 byte & 2);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data2) ],
									 byte & 4);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data3) ],
									 byte & 8);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data4) ],
									 byte & 16);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data5) ],
									 byte & 32);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data6) ],
									 byte & 64);
			digital_operation::write(m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data7) ],
									 byte & 128);
			m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(5.0f);
			m_controller.m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(0.0f);
		}

		inline lcd_controller& controller() { return m_controller; }
		inline i_timer_ptr	   timer() { return m_timer; }

	private:
		lcd_controller			   m_controller;
		std::shared_ptr<std_timer> m_timer;
		std::thread				   m_scheduler_thread;
		std::atomic<bool>		   m_exit_flag;
	};

	BOOST_AUTO_TEST_SUITE(lcd_logic_test_suite)

	BOOST_AUTO_TEST_CASE(print_symbol_test)
	{
		test_framework framework;
		framework.start();

		framework.command(false, 'a');

		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'a');
		framework.stop();
	}

	BOOST_AUTO_TEST_CASE(write_ddram_timing_test)
	{
		test_framework framework;
		// 1s real = 1000us simulated
		framework.set_prescaler(.001f);
		framework.start();

		framework.command(false, 'a');
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'a');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);

		framework.command(false, 'b');
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'a');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), false);

		framework.command(false, 'b');
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'b');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);
		framework.stop();
	}

	BOOST_AUTO_TEST_SUITE_END()
} // namespace lcd
