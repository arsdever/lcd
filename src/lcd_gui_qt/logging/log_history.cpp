#include <stdafx.h>

#include "log_history.h"

namespace lcd
{
	log_history::log_history() = default;

	void log_history::on_updated(updated_e cb) { m_on_updated = cb; }

	void log_history::add_entry(logger::log_level lvl, std::string const& msg)
	{
		m_content.push_back({ lvl, msg });

		if (m_on_updated)
			m_on_updated();
	}

	void* log_history::level(int index) { return &std::get<0>(m_content.at(index)); }

	void* log_history::message(int index) { return &std::get<1>(m_content.at(index)); }

	int log_history::count() const { return m_content.size(); }
} // namespace lcd