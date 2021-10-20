#include <stdafx.h>

#include <logger.h>

#ifndef NO_SPDLOG
#	include <spdlog/spdlog.h>
#	include <spdlog/sinks/stdout_color_sinks.h>
#	include <spdlog/sinks/daily_file_sink.h>

namespace lcd
{
	static std::shared_ptr<spdlog::logger> g_logger;

	namespace
	{
		struct init_spdlog
		{
			init_spdlog()
			{
				// https://spdlog.docsforge.com/v1.x/2.creating-loggers/#creating-loggers-with-multiple-sinks
				std::vector<spdlog::sink_ptr> sinks;
				sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>());
				sinks.push_back(
					std::make_shared<spdlog::sinks::daily_file_sink_st>("lcd_controller.log", 23, 59, true, 5));
				g_logger = std::make_shared<spdlog::logger>("global", begin(sinks), end(sinks));
			}
		};

		static init_spdlog __init_spdlog;
	} // namespace
} // namespace lcd

#	define LOG_METHOD(method, message) g_logger->method(message)
#else
#	define LOG_METHOD(method, message) std::cout << #	 method << ": " << message << std::endl;
#endif

namespace lcd
{
	void logger::info(std::string const& message) { LOG_METHOD(info, message); }
	void logger::warn(std::string const& message) { LOG_METHOD(warn, message); }
	void logger::error(std::string const& message) { LOG_METHOD(error, message); }
	void logger::critical(std::string const& message) { LOG_METHOD(critical, message); }
	void logger::debug(std::string const& message) { LOG_METHOD(debug, message); }
} // namespace lcd