#pragma once

#include <logger.h>
#include <spdlog/spdlog.h>

namespace lcd
{
	spdlog::level::level_enum to_spdlog_level(logger::log_level const& level);
	logger::log_level		  from_spdlog_level(spdlog::level::level_enum const& level);
} // namespace lcd