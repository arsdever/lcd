#pragma once

#include <logging_prototypes.h>

#include <i_log_sink.h>
#include <logger.h>

namespace lcd
{
	class log_history_sink
		: public i_log_sink
		, public std::enable_shared_from_this<log_history_sink>
	{
	public:
		log_history_sink();
		log_history_sink(log_history_wptr history);

		void set_history(log_history_wptr history);

		virtual void add(logger::log_level const& level, std::string const& log_message) override;

	private:
		log_history_wptr m_history;
	};
} // namespace lcd