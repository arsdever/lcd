#pragma once

#include <i_timer.h>
#include <qelapsedtimer>

namespace lcd
{
	class qt_timer : public i_timer
	{
	public:
		qt_timer() = default;

		virtual std::chrono::duration<double> elapsed() const override;

		virtual std::chrono::duration<double> delta() override;

		virtual void set_prescaler(double prescaler) override;

	private:
		QElapsedTimer m_qelapsed_timer;
		double		  m_prescaler;
	};
} // namespace lcd