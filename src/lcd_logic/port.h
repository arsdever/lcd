#pragma once

namespace lcd
{
	template <typename pin_t>
	concept is_pin = requires(pin_t const& t)
	{
		t.get_voltage();
	}
	&&requires(pin_t& t) { t.set_voltage({}); };

	class digital_operation
	{
	public:
		template <typename pin_t>
		requires is_pin<pin_t>
		static inline bool read(pin_t const& pin) { return pin.get_voltage() > 3.0f; }

		template <typename pin_t>
		requires is_pin<pin_t>
		static inline void write(pin_t& pin, bool value) { value ? pin.set_voltage(5.0f) : pin.set_voltage(0.0f); }
	};

	// template <
	//	typename voltage_t,
	//	voltage_t op_voltage,
	//	bool analog,
	//	voltage_t digital_threshold
	//>
	// class pin;

	// template <
	//	typename voltage_t = float,
	//	voltage_t op_voltage = 5.0f,
	//	voltage_t threshold = 2.5f
	//>
	//	class digital_pin
	//{
	// public:
	//	using default_digital_pin = pin<voltage_t, op_voltage, false, threshold>;
	// public:
	//	template <typename pin_t = default_digital_pin>
	//	requires is_pin<pin_t>
	//		inline static constexpr bool state(std::shared_ptr<pin_t> pin) { return pin->get_voltage() > threshold; }

	//	template <typename pin_t = default_digital_pin>
	//	requires is_pin<pin_t>
	//		inline static constexpr void set_state(std::shared_ptr<pin_t> pin, bool state) { return
	// pin->set_voltage(op_voltage); }
	//};

	// template <
	//	typename voltage_t = float,
	//	voltage_t op_voltage = 5.0f,
	//	bool analog = false,
	//	voltage_t digital_threshold = 2.5f
	//>
	//	class pin
	//{
	// public:
	//	using event_handler_t = std::function<void()>;
	//	void on_voltage_changed(event_handler_t const& cb) { m_event_handlers[0] = cb; }
	//	void on_edge_down(event_handler_t const& cb) { m_event_handlers[1] = cb; }
	//	void on_edge_up(event_handler_t const& cb) { m_event_handlers[2] = cb; }
	//	void on_edge_switch(event_handler_t const& cb) { m_event_handlers[2] = cb; }

	//	inline void set_voltage(float value)
	//	{
	//		if (is_analog())
	//			m_voltage = value;
	//		else
	//			m_voltage = op_voltage;
	//		m_event_handlers[0]();
	//	}
	//	inline bool logic_state() const { return m_voltage > digital_threshold; }
	//	inline float get_voltage() const { return m_voltage; }
	//	inline constexpr bool is_analog() const { return analog; }
	//	inline void edge_down() { m_event_handlers[1](); }
	//	inline void edge_up() { m_event_handlers[2](); }
	//	inline void edge_switch() { m_event_handlers[3](); }

	// private:
	//	float m_voltage;
	//	std::array<event_handler_t, 4> m_event_handlers;
	//};

	class pin
	{
	public:
		float get_voltage() const { return m_voltage; }

		void set_voltage(float voltage)
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

	public:
		using event_handler_t = std::function<void()>;
		void on_voltage_changed(event_handler_t const& cb) { m_event_handlers[ 0 ] = cb; }
		void on_edge_down(event_handler_t const& cb) { m_event_handlers[ 1 ] = cb; }
		void on_edge_up(event_handler_t const& cb) { m_event_handlers[ 2 ] = cb; }
		void on_edge_switch(event_handler_t const& cb) { m_event_handlers[ 3 ] = cb; }

	private:
		float						   m_voltage;
		std::array<event_handler_t, 4> m_event_handlers;
	};

	template <int pin_count>
	class port
	{
	public:
		std::array<pin, pin_count> m_pins;
	};
} // namespace lcd