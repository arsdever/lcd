#pragma once

#include <pin.h>

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

	template <int pin_count>
	class port
	{
	public:
		port(std::initializer_list<pin> init)
		{
			auto it = init.begin();
			for (auto& pin : m_pins)
				{
					pin = std::move(*it++);
				}
		}
		std::array<pin, pin_count> m_pins;
	};
} // namespace lcd