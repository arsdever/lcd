#pragma once

#include <logger.h>

namespace lcd
{
	class logger_with_timing
	{
	public:
		static void info(std::chrono::duration<double> const& time, std::string const& message);
		static void warn(std::chrono::duration<double> const& time, std::string const& message);
		static void error(std::chrono::duration<double> const& time, std::string const& message);
		static void critical(std::chrono::duration<double> const& time, std::string const& message);
		static void debug(std::chrono::duration<double> const& time, std::string const& message);
	};
} // namespace lcd