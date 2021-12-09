#include <stdafx.h>

#include <step_timer.h>

namespace lcd
{
	step_timer::step_timer() : m_elapsed_time {}, m_prescaler { 1 } { }

	std::chrono::duration<double> step_timer::elapsed() const { return m_elapsed_time; }

	void step_timer::frame() { m_elapsed_time += delta(); }

	std::chrono::duration<double> step_timer::delta() const { return std::chrono::duration<double> { m_prescaler }; }

	void step_timer::set_prescaler(double prescaler) { m_prescaler = prescaler; }

	double step_timer::prescaler() const { return m_prescaler; }
} // namespace lcd
