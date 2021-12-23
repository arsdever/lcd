#pragma once

#include <lcd_logic_prototypes.h>

namespace lcd
{
	class scheduler
	{
	public:
		using task_t		   = std::function<void()>;
		using duration_t	   = std::chrono::duration<double>;
		using schedule_entry_t = std::tuple<task_t, duration_t, size_t, std::chrono::system_clock::time_point>;
		using schedule_t	   = std::list<schedule_entry_t>;
		using task_id_t		   = uint64_t;

		enum class state
		{
			stopped,
			paused,
			running
		};

	public:
		scheduler();
		scheduler(timer_wptr timer);

		void	   set_timer(timer_wptr timer);
		timer_wptr timer() const;
		task_id_t  add_task(task_t	   task,
							duration_t delay,
							bool	   sequental = false,
							task_id_t			 = std::numeric_limits<task_id_t>::max());
		void	   start();
		void	   run();
		void	   pause();
		void	   stop();
		void	   tick();
		state	   get_state() const;

	private:
		void push_task(schedule_entry_t const& entry);

	private:
		task_id_t	m_task_id_counter;
		schedule_t	m_tasks;
		timer_wptr	m_timer;
		state		m_state;
		std::thread m_execution_thread;
		std::mutex	m_tasks_mutex;
	};
} // namespace lcd
