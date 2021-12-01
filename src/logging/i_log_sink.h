#pragma once

#include <logger.h>

namespace lcd
{
	class i_log_sink
	{
	public:
		virtual ~i_log_sink() = default;

		virtual void add(logger::log_level const& lvl, std::string const& msg) = 0;
	};
} // namespace lcd