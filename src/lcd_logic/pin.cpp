#include <stdafx.h>

#include "pin.h"

namespace lcd
{
	pin::pin() : pin("undefined", -1) { }

	pin::pin(std::string const& name, int index) : m_name(name), m_pin_index(index) { }

	float pin::get_voltage() const { return m_voltage; }

	void pin::set_voltage(float voltage)
	{
		if (m_voltage < 0.2f)
			{
				if (voltage > 4.7f)
					{
						if (m_event_handlers[ 2 ])
							m_event_handlers[ 2 ]();
						if (m_event_handlers[ 3 ])
							m_event_handlers[ 3 ]();
					}
			}

		if (m_voltage > 4.7f)
			{
				if (voltage < 0.2f)
					{
						if (m_event_handlers[ 1 ])
							m_event_handlers[ 1 ]();
						if (m_event_handlers[ 3 ])
							m_event_handlers[ 3 ]();
					}
			}

		m_voltage = voltage;
		if (m_event_handlers[ 0 ])
			m_event_handlers[ 0 ]();
	}

	void pin::on_voltage_changed(event_handler_t const& cb) { m_event_handlers[ 0 ] = cb; }

	void pin::on_edge_down(event_handler_t const& cb) { m_event_handlers[ 1 ] = cb; }

	void pin::on_edge_up(event_handler_t const& cb) { m_event_handlers[ 2 ] = cb; }

	void pin::on_edge_switch(event_handler_t const& cb) { m_event_handlers[ 3 ] = cb; }
} // namespace lcd
