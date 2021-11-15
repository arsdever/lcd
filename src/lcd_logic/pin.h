#pragma once

#include <event.h>

namespace lcd
{
	class pin
	{
	public:
		using voltage_t	   = double;
		using event_t	   = event<>;
		using connection_t = event<>::connection_t;

	public:
		enum class event_types_enum
		{
			on_voltage_changed,
			on_edge_down,
			on_edge_up,
			on_edge_switch
		};

		pin();
		pin(std::string const& pin_name, int index);

		float		 get_voltage() const;
		void		 set_voltage(float voltage);
		connection_t register_to_event(event_types_enum et, event_t::handler_t const& cb);
		void		 unregister_from_event(connection_t con);

		std::string const& get_name() const;
		int				   get_index() const;

	private:
		std::string			   m_name;
		int					   m_pin_index;
		double				   m_voltage;
		std::array<event_t, 4> m_events;
	};
} // namespace lcd