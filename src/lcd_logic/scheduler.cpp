#include <stdafx.h>

#include <scheduler.h>

namespace lcd
{
	scheduler::scheduler() : m_timer(), m_task_id_counter { 0 }, m_state { state::running } { }

	scheduler::scheduler(i_timer_wptr timer) : m_timer(timer), m_task_id_counter { 0 } { }

	void scheduler::set_timer(i_timer_wptr timer) { m_timer = timer; }

	i_timer_wptr scheduler::timer() const { return m_timer; }

	void scheduler::add_task(task_t task, duration_t delay)
	{
		m_tasks.push_back({ task, delay, m_task_id_counter++, std::chrono::system_clock::now() });
	}

	void scheduler::start()
	{
		if (i_timer_ptr timer = m_timer.lock())
			timer->delta();

		m_execution_thread = std::thread { [ = ] {
			while (m_state != state::stopped)
				{
					if (m_state == state::running)
						tick();
				}
		} };
	}

	void scheduler::run() { m_state = state::running; }

	void scheduler::pause() { m_state = state::paused; }

	void scheduler::stop()
	{
		m_state = state::stopped;
		m_execution_thread.join();
	}

	void scheduler::tick()
	{
		if (i_timer_ptr timer = m_timer.lock())
			{
				timer->frame();
				duration_t delta = timer->delta();
				auto	   it	 = m_tasks.begin();
				while (it != m_tasks.end())
					{
						auto tmp = it;
						++it;
						std::get<1>(*tmp) -= delta;
						if (std::get<1>(*tmp) < std::chrono::nanoseconds { 0 })
							{
								std::get<0> (*tmp)();
								m_tasks.erase(tmp);
							}
					}
			}
	}

	scheduler::state scheduler::get_state() const { return m_state; }
} // namespace lcd
