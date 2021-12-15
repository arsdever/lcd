#pragma once

#include <i_log_history.h>

namespace lcd
{
	class log_history
		: public i_log_history
		, public std::enable_shared_from_this<log_history>
	{
	private:
		template <typename T>
		using container_t = std::vector<T>;
		using updated_e	  = std::function<void()>;
		using entry_t	  = std::tuple<logger::log_level, std::string>;

	public:
		log_history();

		void on_updated(updated_e cb);

		virtual void add_entry(logger::log_level lvl, std::string const& message) override;

		void* level(int index);

		void* message(int index);

		int count() const;

	private:
		container_t<entry_t> m_content;
		updated_e			 m_on_updated;
	};
} // namespace lcd