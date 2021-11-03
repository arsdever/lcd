#pragma once

namespace lcd
{
	class i_timer;
	using i_timer_ptr  = std::shared_ptr<i_timer>;
	using i_timer_wptr = std::weak_ptr<i_timer>;
	using i_timer_uptr = std::unique_ptr<i_timer>;

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
		/// has passed sice the last frame call.
		///
		/// @return the duration since the last delta was called.
		virtual std::chrono::duration<double> delta() const = 0;

		/// @brief Tells the timer that a frame has passed.
		///
		/// @details This function is mostly used to update the delta time between
		/// the frames.
		virtual void frame() = 0;

		/// @brief Sets the timer prescaler.
		///
		/// @details The prescaler is used by the timer to change the actual
		/// timing values depending on the user's needs.
		///
		/// @param prescaler the value to be set.
		virtual void set_prescaler(double prescaler) = 0;

		/// @brief Get the prescaler currently set on the timer.
		/// @return the prescaler
		virtual double prescaler() const = 0;
	};
} // namespace lcd
