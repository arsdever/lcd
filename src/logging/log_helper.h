#pragma once

#include <logger.h>

namespace lcd
{
	inline std::string to_string(logger::log_level const& lvl)
	{
		switch (lvl)
			{
			case logger::log_level::critical: return "critical";
			case logger::log_level::debug: return "debug";
			case logger::log_level::error: return "error";
			case logger::log_level::info: return "info";
			case logger::log_level::warn: return "warning";
			}
	}
} // namespace lcd