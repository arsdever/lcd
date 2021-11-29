#pragma once

#include <logger.h>
#include <logging_prototypes.h>

namespace lcd
{
	class log_history_sink : public std::enable_shared_from_this<log_history_sink>
	{
	public:
		log_history_sink(log_history_wptr history);

		void add(logger::log_level level, std::string const& log_message);

	private:
		log_history_wptr m_history;
	};
} // namespace lcd