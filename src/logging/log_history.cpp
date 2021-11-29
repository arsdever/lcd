#include <stdafx.h>

#include "log_history.h"

namespace lcd
{
	log_history::log_history() { }

	void log_history::add_entry(logger::log_level lvl, std::string const& message)
	{
		m_entries[ lvl ].push_back(message);
	}
} // namespace lcd