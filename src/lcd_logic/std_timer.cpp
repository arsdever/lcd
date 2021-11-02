#include <stdafx.h>

#include <std_timer.h>

namespace lcd
{
	std_timer::std_timer()
		: m_elapsed_time {}, m_last_tick { std::chrono::high_resolution_clock::now() }, m_delta { 0 }, m_prescaler { 1 }
	{
	}

	std::chrono::duration<double> std_timer::elapsed() const { return m_elapsed_time; }

	void std_timer::frame()
	{
		std::chrono::duration t	   = std::chrono::high_resolution_clock::now() - m_last_tick;
		std::chrono::duration diff = std::chrono::duration<double>(t) * m_prescaler;
		m_elapsed_time += diff;
		m_last_tick += t;
		m_delta = diff;
	}

	std::chrono::duration<double> std_timer::delta() const { return m_delta; }

	void std_timer::set_prescaler(double prescaler) { m_prescaler = prescaler; }
} // namespace lcd