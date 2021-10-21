#pragma once

#include <i_timer.h>

namespace lcd
{
	class std_timer : public i_timer
	{
	public:
		std_timer();

		virtual std::chrono::duration<double> elapsed() const override;

		virtual void frame() override;

		virtual std::chrono::duration<double> delta() const override;

		virtual void set_prescaler(double prescaler) override;

	private:
		std::chrono::high_resolution_clock::time_point m_creation_timepoint;
		std::chrono::high_resolution_clock::time_point m_last_tick;
		std::chrono::duration<double>				   m_delta;
		double										   m_prescaler;
	};
} // namespace lcd
