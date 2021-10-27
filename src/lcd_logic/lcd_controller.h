#pragma once

#include "port.h"

namespace lcd
{
	class lcd_controller;
	using lcd_controller_ptr  = std::shared_ptr<lcd_controller>;
	using lcd_controller_wptr = std::weak_ptr<lcd_controller>;

	class lcd_controller
	{
	public:
		enum class interface_type_enum
		{
			four_pin_interface,
			eight_pin_interface
		};

		enum class display_lines_mode_enum
		{
			single_line,
			double_line
		};

		enum class fonts_enum
		{
			five_eight,
			five_ten
		};

		enum class registers_mode_enum
		{
			instruction,
			data
		};

		enum class read_write_mode_enum
		{
			write,
			read
		};

		enum class address_mode
		{
			cgram,
			ddram
		};

		enum class cursor_direction_enum : bool
		{
			decrement = 0,
			increment = 1,
			left	  = decrement,
			right	  = increment
		};

		enum class command_types_enum
		{
			clear,
			return_home,
			entry_mode_set,
			display_on_off_control,
			cursor_or_display_shift,
			function_set,
			set_cgram_address,
			set_ddram_address,
			read_busy_flag_and_address,
			write_data_to_cg_or_ddram,
			read_data_from_cg_or_ddram
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

		struct execution_data
		{
			read_write_mode_enum rw_mode;
			registers_mode_enum	 rs_mode;
			uint8_t				 data;
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

		using on_update_delegate = std::function<void()>;

		static std::unordered_map<command_types_enum, std::chrono::nanoseconds> s_execution_time_map;

	public:
		lcd_controller();
		virtual ~lcd_controller() = default;

		void		register_for_updates(on_update_delegate callback);
		char&		symbol_at_ddram(size_t address);
		const char& symbol_at_ddram(size_t address) const;
		bool		is_busy() const;

		interface_type_enum		interface_type() const;
		display_lines_mode_enum lines() const;
		fonts_enum				font() const;

	protected:
		virtual void port_updated_callback(pinout p);
		virtual void execute(execution_data const& data);

	private:
		void	on_enable_falling_edge();
		void	value_to_bus(uint8_t value);
		uint8_t value_from_bus();

	public:
		port<16>				m_port;
		interface_type_enum		m_interface_type;
		display_lines_mode_enum m_display_lines_mode;
		fonts_enum				m_font;
		on_update_delegate		m_on_update_cb;
		size_t					m_hscroll;
		size_t					m_vscroll;
		bool					m_cursor_show;
		cursor_direction_enum	m_cursor_move_direction;
		bool					m_insert;
		bool					m_blink;
		std::atomic<bool>		m_busy;
		bool					m_display_on;
		bool					m_scroll_direction;
		address_mode			m_address_mode;
		std::array<char, 9920>	m_cgrom;
		size_t					m_cgram_address_counter;
		std::array<char, 64>	m_cgram;
		size_t					m_ddram_address_counter;
		std::array<char, 128>	m_ddram;
	};
} // namespace lcd