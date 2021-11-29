#pragma once

#include <logger.h>

namespace lcd
{
	class log_history
	{
	public:
		using history_t = std::unordered_map<logger::log_level, std::list<std::string>>;

	public:
		log_history();

		void add_entry(logger::log_level lvl, std::string const& message);

	private:
		history_t m_entries;
	};
} // namespace lcd
