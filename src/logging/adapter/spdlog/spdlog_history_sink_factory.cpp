#include <stdafx.h>

#include <adapter/spdlog/spdlog_history_sink.h>
#include <factory/log_history_sink_factory.h>

namespace lcd
{
	log_history_sink_ptr log_history_sink_factory::create(log_history_wptr history)
	{
		return std::make_shared<spdlog_history_sink>(history);
	}
} // namespace lcd
