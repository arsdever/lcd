#pragma once

namespace lcd
{
	class pin
	{
	public:
		using voltage_t		   = double;
		using event_handler_t = std::function<void()>;
		using event_handlers_t = std::array<event_handler_t, 4>;

	public:
		pin();
		pin(std::string const& pin_name, int index);

		float get_voltage() const;
		void  set_voltage(float voltage);
		void  on_voltage_changed(event_handler_t const& cb);
		void  on_edge_down(event_handler_t const& cb);
		void  on_edge_up(event_handler_t const& cb);
		void  on_edge_switch(event_handler_t const& cb);

	private:
		std::string		 m_name;
		int				 m_pin_index;
		double			 m_voltage;
		event_handlers_t m_event_handlers;
	};
} // namespace lcd