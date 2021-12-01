#pragma once

#include <logging_prototypes.h>

namespace lcd
{
	class log_history_sink_factory
	{
	public:
		static log_history_sink_ptr create(log_history_wptr history);
	};
} // namespace lcd