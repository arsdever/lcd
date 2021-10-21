#include <stdafx.h>

#include <std_timer.h>

namespace lcd
{
	std_timer::std_timer()
		: m_creation_timepoint(std::chrono::high_resolution_clock::now()),
		  m_last_tick { m_creation_timepoint }, m_delta { 0 }, m_prescaler { 1 }
	{
	}

	std::chrono::duration<double> std_timer::elapsed() const
	{
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_creation_timepoint) *
			   m_prescaler;
	}

	void std_timer::frame()
	{
		std::chrono::duration t = std::chrono::high_resolution_clock::now() - m_last_tick;
		m_last_tick += t;
		m_delta = std::chrono::duration<double>(t) * m_prescaler;
	}

	std::chrono::duration<double> std_timer::delta() const { return m_delta; }

	void std_timer::set_prescaler(double prescaler) { m_prescaler = prescaler; }
} // namespace lcd