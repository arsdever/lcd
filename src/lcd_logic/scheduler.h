#pragma once

namespace lcd
{
	class scheduler
	{
	public:
		using task_t = std::function<void()>;
	public:
		scheduler();

		void add_task(task_t task, std::chrono::nanoseconds after);
		void tick(std::chrono::nanoseconds delta);

	private:
		size_t m_task_id_counter;
		std::list<std::tuple<task_t, std::chrono::nanoseconds, size_t, std::chrono::system_clock::time_point>> m_tasks;
	};
}
