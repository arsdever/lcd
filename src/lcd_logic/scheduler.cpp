#include <stdafx.h>

#include "scheduler.h"

#include "i_timer.h"

namespace lcd
{
	scheduler::scheduler() : m_timer(), m_task_id_counter { 0 }, m_state { state::running } { }

	scheduler::scheduler(timer_wptr timer) : m_timer(timer), m_task_id_counter { 0 } { }

	void scheduler::set_timer(timer_wptr timer) { m_timer = timer; }

	timer_wptr scheduler::timer() const { return m_timer; }

	scheduler::task_id_t scheduler::add_task(task_t task, duration_t delay, bool sequental, task_id_t after)
	{
		std::lock_guard<std::mutex> lock(m_tasks_mutex);
		if (sequental)
			{
				schedule_t::iterator task_with_id;
				for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
					{
						if (std::get<2>(*it) == after)
							{
								task_with_id = it;
								break;
							}

						task_with_id = it;
					}

				delay += std::get<1>(*task_with_id);
			}
		push_task({ task, delay, m_task_id_counter++, std::chrono::system_clock::now() });
		return m_task_id_counter;
	}

	void scheduler::start()
	{
		if (timer_ptr timer = m_timer.lock())
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
		std::lock_guard<std::mutex> lock(m_tasks_mutex);
		if (timer_ptr timer = m_timer.lock())
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

	void scheduler::push_task(schedule_entry_t const& entry)
	{
		static constexpr auto schedule_entry_comparer = [](schedule_entry_t const& a,
														   schedule_entry_t const& b) -> bool {
			return std::get<1>(a) > std::get<1>(b);
		};

		auto it = std::find_if(m_tasks.begin(), m_tasks.end(), [ &entry ](schedule_entry_t const& item) -> bool {
			return schedule_entry_comparer(item, entry);
		});
		m_tasks.insert(it, entry);
	}
} // namespace lcd
