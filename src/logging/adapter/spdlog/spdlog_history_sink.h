#pragma once

#include <logging_prototypes.h>

#include "spdlog_helper.h"

#include <log_history_sink.h>
#include <spdlog/sinks/base_sink.h>

// https://spdlog.docsforge.com/v1.x/4.sinks/#implementing-your-own-sink
namespace lcd
{
	class spdlog_history_sink
		: public log_history_sink
		, public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		spdlog_history_sink();
		spdlog_history_sink(log_history_wptr history);

		void sink_it_(const spdlog::details::log_msg& msg) override;

		void flush_() override;
	};
} // namespace lcd