#pragma once

namespace lcd
{
	class i_timer
	{
	public:
		using task_t = std::function<void()>;

	public:
		virtual ~i_timer() = default;

		/// @return the duration since the timer was created.
		virtual std::chrono::duration<double> elapsed() const = 0;

		/// @brief Duration between iterations.
		///
		/// @details Every time the function is called it will tell how much time
		/// has passed sice the last time it was called multiplied by the
		/// prescaler currently set on the timer. For example, if the actual time
		/// passed since the last call is 100ms and the prescaler is set to be
		/// 10.0f then the return value will be equal to 1000ms.
		///
		/// @return the duration since the last delta was called.
		virtual std::chrono::duration<double> delta() = 0;

		/// @brief Sets the timer prescaler.
		///
		/// @details The prescaler is used by the timer to change the actual
		/// timing values depending on the user's needs.
		///
		/// @param prescaler the value to be set.
		virtual void set_prescaler(double prescaler) = 0;
	};
} // namespace lcd
