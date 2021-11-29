#include <stdafx.h>

#include "spdlog_history_sink.h"

namespace lcd
{
	spdlog_history_sink::spdlog_history_sink(log_history_wptr history) : log_history_sink(history) { }

	void spdlog_history_sink::sink_it_(const spdlog::details::log_msg& msg)
	{
		add(from_spdlog_level(msg.level), fmt::to_string(msg.payload));
	}

	void spdlog_history_sink::flush_() { }
} // namespace lcd
