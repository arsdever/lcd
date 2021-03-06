#include <stdafx.h>
#define BOOST_TEST_MODULE lcd_logic
#include <boost/test/unit_test.hpp>
#include <condition_variable>
#include <lcd_controller.h>
#include <logger.h>
#include <mutex>
#include <scheduler.h>
#include <step_timer.h>

lcd::scheduler g_scheduler {};

namespace lcd
{
	class test_framework
	{
	public:
		inline test_framework() : m_exit_flag { false }
		{
			logger::set_log_level(logger::log_level::error);
			m_timer		 = std::make_shared<step_timer>();
			m_controller = std::make_shared<lcd_controller>();
			g_scheduler.set_timer(m_timer);
		}

		inline ~test_framework() { stop(); }

		inline void set_prescaler(double prescaler) { m_timer->set_prescaler(prescaler); }

		inline void start() { g_scheduler.start(); }

		inline void stop() { g_scheduler.stop(); }

		inline uint8_t read_bus() const
		{
			uint8_t value = 0;
			for (int i = static_cast<int>(lcd_controller::pinout::data7);
				 i >= static_cast<int>(lcd_controller::pinout::data0);
				 --i)
				{
					value <<= 1;
					value |= static_cast<uint8_t>(digital_operation::read(m_controller->m_port.m_pins[ i ]));
				}
			return value;
		}

		inline void command(bool rs, bool rw, uint8_t byte)
		{
			m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rw) ].set_voltage(rw ? 5.0f
																											: 0.0f);
			m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::rs) ].set_voltage(rs ? 5.0f
																											: 0.0f);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data0) ], byte & 1);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data1) ], byte & 2);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data2) ], byte & 4);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data3) ], byte & 8);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data4) ], byte & 16);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data5) ], byte & 32);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data6) ], byte & 64);
			digital_operation::write(
				m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::data7) ], byte & 128);
			m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(5.0f);
			m_controller->m_port.m_pins[ static_cast<int>(lcd::lcd_controller::pinout::en) ].set_voltage(0.0f);
		}

		inline void wait_for(std::chrono::duration<double> dur)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			g_scheduler.add_task([ &cv = m_condition_variable ] { cv.notify_one(); }, dur);
			m_condition_variable.wait(lock);
		}

		inline lcd_controller& controller() { return *m_controller; }
		inline timer_ptr	   timer() { return m_timer; }

	private:
		lcd_controller_ptr		m_controller;
		timer_ptr				m_timer;
		std::thread				m_scheduler_thread;
		std::atomic<bool>		m_exit_flag;
		std::condition_variable m_condition_variable;
		std::mutex				m_mutex;
	};

	BOOST_AUTO_TEST_SUITE(lcd_logic_test_suite)

	BOOST_AUTO_TEST_CASE(print_symbol_test)
	{
		test_framework framework;
		framework.set_prescaler(1e-9);
		framework.start();

		framework.command(true, false, 'a');

		framework.wait_for(std::chrono::microseconds(40));
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'a');
	}

	BOOST_AUTO_TEST_CASE(write_ddram_timing_test)
	{
		test_framework framework;
		framework.set_prescaler(1e-9);
		framework.start();

		framework.command(true, false, 'a');
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 0);
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);

		framework.command(true, false, 'b');
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(1), 0);
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);

		framework.wait_for(std::chrono::microseconds(20));
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 0);
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(1), 0);

		framework.wait_for(std::chrono::microseconds(20));
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), false);
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0), 'a');

		framework.command(true, false, 'b');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);
		framework.wait_for(std::chrono::microseconds(40));
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(1), 'b');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), false);
	}

	BOOST_AUTO_TEST_CASE(set_ddram_address)
	{
		test_framework framework;
		framework.set_prescaler(1e-9);
		framework.start();

		framework.command(false, false, 0x85);
		framework.wait_for(std::chrono::microseconds(40));
		framework.command(false, true, 0);
		BOOST_CHECK_EQUAL(framework.read_bus(), 0x05);
		framework.command(true, false, 'a');
		framework.wait_for(std::chrono::microseconds(40));
		BOOST_CHECK_EQUAL(framework.controller().symbol_at_ddram(0x05), 'a');
	}

	BOOST_AUTO_TEST_CASE(busy_flag)
	{
		test_framework framework;
		framework.set_prescaler(1e-9);
		framework.start();

		framework.command(true, false, 'a');
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), true);
		framework.command(false, true, 0);
		BOOST_CHECK_EQUAL(framework.read_bus(), 0x80);
		framework.wait_for(std::chrono::microseconds(40));
		BOOST_CHECK_EQUAL(framework.controller().is_busy(), false);
		framework.command(false, true, 0);
		BOOST_CHECK_EQUAL(framework.read_bus(), 0x01);
	}

	BOOST_AUTO_TEST_SUITE_END()
} // namespace lcd
