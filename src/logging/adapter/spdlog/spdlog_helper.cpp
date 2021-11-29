#include <stdafx.h>

#include "spdlog_helper.h"

namespace lcd
{
	logger::log_level from_spdlog_level(spdlog::level::level_enum const& level)
	{
		switch (level)
			{
			case spdlog::level::level_enum::info: return logger::log_level::info;
			case spdlog::level::level_enum::debug: return logger::log_level::debug;
			case spdlog::level::level_enum::warn: return logger::log_level::warn;
			case spdlog::level::level_enum::err: return logger::log_level::error;
			case spdlog::level::level_enum::critical: return logger::log_level::critical;
			}

		return logger::log_level::info;
	}

	spdlog::level::level_enum to_spdlog_level(logger::log_level const& level)
	{
		switch (level)
			{
			case logger::log_level::info: return spdlog::level::level_enum::info;
			case logger::log_level::debug: return spdlog::level::level_enum::debug;
			case logger::log_level::warn: return spdlog::level::level_enum::warn;
			case logger::log_level::error: return spdlog::level::level_enum::err;
			case logger::log_level::critical: return spdlog::level::level_enum::critical;
			}

		return spdlog::level::level_enum::info;
	}
} // namespace lcd
