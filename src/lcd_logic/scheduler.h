#pragma once

#include <i_timer.h>

namespace lcd
{
	class scheduler
	{
	public:
		using task_t	 = std::function<void()>;
		using duration_t = std::chrono::duration<double>;
		using schedule_t = std::list<std::tuple<task_t, duration_t, size_t, std::chrono::system_clock::time_point>>;

	public:
		scheduler(std::function<std::unique_ptr<i_timer>()> timer_factory);

		void add_task(task_t task, duration_t delay);
		void start();
		void tick();

	private:
		size_t					 m_task_id_counter;
		schedule_t				 m_tasks;
		std::unique_ptr<i_timer> m_timer;
	};
} // namespace lcd
