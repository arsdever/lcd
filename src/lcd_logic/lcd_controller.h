#pragma once

#include "port.h"

namespace lcd
{
	class lcd_controller
	{
	public:
		enum class interface_type_enum
		{
			undefined,
			four_pin_interface,
			eight_pin_interface
		};

		enum class registers_mode_enum
		{
			instruction,
			data
		};

		enum class read_write_mode_enum
		{
			read,
			write
		};

		enum class pinout
		{
			ground,
			vcc,
			v0,
			rs,
			rw,
			en,
			data0,
			data1,
			data2,
			data3,
			data4,
			data5,
			data6,
			data7,
			anode,
			catode
		};

		inline static constexpr std::string pin_name(pinout p)
		{
			switch (p)
			{
			case pinout::ground: return "ground";
			case pinout::vcc: return "vcc";
			case pinout::v0: return "v0";
			case pinout::rs: return "rs";
			case pinout::rw: return "rw";
			case pinout::en: return "en";
			case pinout::data0: return "data0";
			case pinout::data1: return "data1";
			case pinout::data2: return "data2";
			case pinout::data3: return "data3";
			case pinout::data4: return "data4";
			case pinout::data5: return "data5";
			case pinout::data6: return "data6";
			case pinout::data7: return "data7";
			case pinout::anode: return "anode";
			case pinout::catode: return "catode";
			}
		}

	public:
		lcd_controller();
		virtual ~lcd_controller() = default;

	protected:
		virtual void port_updated_callback(pinout p);
		virtual void handle_command(uint8_t command);
		virtual void handle_data(uint8_t data);

	public:
		port<16> m_port;
		interface_type_enum m_interface_type;
	};
}