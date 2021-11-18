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
						m_events[ static_cast<int>(event_types_enum::on_edge_up) ].invoke();
						m_events[ static_cast<int>(event_types_enum::on_edge_switch) ].invoke();
					}
			}

		if (m_voltage > 4.7f)
			{
				if (voltage < 0.2f)
					{
						m_events[ static_cast<int>(event_types_enum::on_edge_down) ].invoke();
						m_events[ static_cast<int>(event_types_enum::on_edge_switch) ].invoke();
					}
			}

		m_voltage = voltage;
		m_events[ static_cast<int>(event_types_enum::on_voltage_changed) ].invoke();
	}

	pin::connection_t pin::register_to_event(event_types_enum et, event_t::handler_t const& cb)
	{
		return m_events[ static_cast<int>(et) ] += cb;
	}

	void pin::unregister_from_event(connection_t con) { con.disconnect(); }
} // namespace lcd
