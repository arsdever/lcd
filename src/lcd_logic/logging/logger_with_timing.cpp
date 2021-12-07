#include "stdafx.h"

#include "logger_with_timing.h"

#include "timer_helper_functions.h"

namespace lcd
{
	void logger_with_timing::info(std::chrono::duration<double> const& time, std::string const& message)
	{
		logger::info(to_string(time) + '|'  + message);
	}

	void logger_with_timing::warn(std::chrono::duration<double> const& time, std::string const& message)
	{
		logger::warn(to_string(time) + '|'  + message);
	}

	void logger_with_timing::error(std::chrono::duration<double> const& time, std::string const& message)
	{
		logger::error(to_string(time) + '|'  + message);
	}

	void logger_with_timing::critical(std::chrono::duration<double> const& time, std::string const& message)
	{
		logger::critical(to_string(time) + '|'  + message);
	}

	void logger_with_timing::debug(std::chrono::duration<double> const& time, std::string const& message)
	{
		logger::debug(to_string(time) + '|'  + message);
	}
} // namespace lcd