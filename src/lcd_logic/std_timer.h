#pragma once

#include <i_timer.h>

namespace lcd
{
	class std_timer : public i_timer
	{
	public:
		std_timer();

		virtual std::chrono::duration<double> elapsed() const override;

		virtual std::chrono::duration<double> delta() override;

		virtual void set_prescaler(double prescaler) override;

	private:
		std::chrono::high_resolution_clock::time_point m_creation_timepoint;
		std::chrono::high_resolution_clock::time_point m_last_tick;
		double										   m_prescaler;
	};
} // namespace lcd
