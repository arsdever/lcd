#include <stdafx.h>

#include "log_history_sink.h"

#include "i_log_history.h"

namespace lcd
{
	log_history_sink::log_history_sink() = default;

	log_history_sink::log_history_sink(log_history_wptr history) : m_history(history) { }

	void log_history_sink::set_history(log_history_wptr history) { m_history = history; }

	void log_history_sink::add(logger::log_level const& level, std::string const& log_message)
	{
		if (log_history_ptr history = m_history.lock())
			{
				history->add_entry(level, log_message);
			}
	}
} // namespace lcd