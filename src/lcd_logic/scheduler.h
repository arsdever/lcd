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
		using task_id_t	 = uint64_t;

		enum class state
		{
			stopped,
			paused,
			running
		};

	public:
		scheduler();
		scheduler(i_timer_wptr timer);

		void		 set_timer(i_timer_wptr timer);
		i_timer_wptr timer() const;
		task_id_t	 add_task(task_t task, duration_t delay, bool sequental = false, task_id_t = std::numeric_limits<task_id_t>::max());
		void		 start();
		void		 run();
		void		 pause();
		void		 stop();
		void		 tick();
		state		 get_state() const;

	private:
		task_id_t	 m_task_id_counter;
		schedule_t	 m_tasks;
		i_timer_wptr m_timer;
		state		 m_state;
		std::thread	 m_execution_thread;
	};
} // namespace lcd
