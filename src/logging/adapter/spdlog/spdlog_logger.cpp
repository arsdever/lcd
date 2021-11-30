#include <stdafx.h>

#include "logger.h"
#include "spdlog_helper.h"
#include "spdlog_history_sink.h"

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define LOG_METHOD(method, message) g_logger->method(message)
#define SET_LOG_LEVEL(level)		g_logger->set_level(to_spdlog_level(level))

namespace lcd
{
	std::shared_ptr<spdlog::logger> g_logger;

	struct init_spdlog
	{
		init_spdlog()
		{
			// https://spdlog.docsforge.com/v1.x/2.creating-loggers/#creating-loggers-with-multiple-sinks
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("lcd_controller.log", 23, 59, true, 5));
			g_logger = std::make_shared<spdlog::logger>("global", begin(sinks), end(sinks));
		}
	};

	static init_spdlog __init_spdlog;

	void logger::set_log_level(log_level const& level) { SET_LOG_LEVEL(level); }
	void logger::info(std::string const& message) { LOG_METHOD(info, message); }
	void logger::warn(std::string const& message) { LOG_METHOD(warn, message); }
	void logger::error(std::string const& message) { LOG_METHOD(error, message); }
	void logger::critical(std::string const& message) { LOG_METHOD(critical, message); }
	void logger::debug(std::string const& message) { LOG_METHOD(debug, message); }
} // namespace lcd
