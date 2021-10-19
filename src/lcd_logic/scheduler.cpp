#include <stdafx.h>

#include <scheduler.h>

namespace lcd
{
	scheduler::scheduler(std::function<std::unique_ptr<i_timer>()> timer_factory)
		: m_timer(timer_factory()), m_task_id_counter { 0 }
	{
	}

	void scheduler::add_task(task_t task, duration_t delay)
	{
		m_tasks.push_back({ task, delay, m_task_id_counter++, std::chrono::system_clock::now() });
	}

	void scheduler::start() { m_timer->delta(); }

	void scheduler::tick()
	{
		duration_t delta = m_timer->delta();
		auto	   it	 = m_tasks.begin();
		while (it != m_tasks.end())
			{
				auto tmp = it;
				++it;
				std::get<1>(*tmp) -= delta;
				if (std::get<1>(*tmp) < std::chrono::nanoseconds { 0 })
					{
						std::cout << std::get<2>(*tmp) << " : task finished in "
								  << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(
										 std::chrono::system_clock::now() - std::get<3>(*tmp))
										 .count()
								  << " milliseconds" << std::endl;
						std::get<0> (*tmp)();
						m_tasks.erase(tmp);
					}
			}
	}
} // namespace lcd
