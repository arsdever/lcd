#include <stdafx.h>

#include <std_timer.h>

namespace lcd
{
	std_timer::std_timer() : m_creation_timepoint(std::chrono::high_resolution_clock::now()) { }

	std::chrono::duration<double> std_timer::elapsed() const
	{
		return std::chrono::high_resolution_clock::now() - m_creation_timepoint;
	}

	std::chrono::duration<double> std_timer::delta()
	{
		std::chrono::duration t = std::chrono::high_resolution_clock::now() - m_last_tick;
		m_last_tick += t;
		return std::chrono::duration_cast<std::chrono::duration<double>>(t) * m_prescaler;
	}

	void std_timer::set_prescaler(double prescaler) { m_prescaler = prescaler; }
} // namespace lcd