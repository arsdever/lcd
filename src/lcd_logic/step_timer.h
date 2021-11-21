#pragma once

#include <i_timer.h>

namespace lcd
{
	class step_timer : public i_timer
	{
	public:
		step_timer();

		virtual std::chrono::duration<double> elapsed() const override;

		virtual void frame() override;

		virtual std::chrono::duration<double> delta() const override;

		virtual void set_prescaler(double prescaler) override;

		virtual double prescaler() const;

	private:
		std::chrono::duration<double>				   m_elapsed_time;
		double										   m_prescaler;
	};
} // namespace lcd