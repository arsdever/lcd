// === TODO list ===============================================================
// [ ] implement the delta function
// =============================================================================

#include <stdafx.h>

#include <lcd_assert.h>
#include <qt_timer.h>

namespace lcd
{
	std::chrono::duration<double> qt_timer::elapsed() const
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(
			std::chrono::nanoseconds(m_qelapsed_timer.nsecsElapsed()));
	}

	std::chrono::duration<double> qt_timer::delta()
	{
		lcd_assert(false, "qt_timer::delta is not implemented");
		return std::chrono::duration<double> {};
	}

	void qt_timer::set_prescaler(double prescaler) { m_prescaler = prescaler; }
} // namespace lcd