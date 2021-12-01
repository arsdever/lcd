#pragma once

#include <logger.h>

namespace lcd
{
	class i_log_history
	{
	public:
		using history_t = std::vector<std::tuple<logger::log_level, std::string>>;

	public:
		virtual void add_entry(logger::log_level lvl, std::string const& message) = 0;
	};
} // namespace lcd
