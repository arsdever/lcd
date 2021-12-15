#pragma once

#include <lcd_logic_prototypes.h>

#include <i_symbol_getter.h>

namespace lcd
{
	class display : public i_symbol_getter
	{
	public:
		enum class update_reason_enum
		{
			general_update,
			content_changed,
			brightness_changed,
			pin_state_changed
		};

	public:
		using event_t = std::function<void()>;

	public:
		display(size_t width, size_t height);
		virtual ~display() = default;

		virtual void update(update_reason_enum reason);

		void set_controller(lcd_controller_wptr controller);
		void on_controller_changed(event_t callback);

	protected:
		virtual uint8_t address_of_symbol(size_t row, size_t column) const;
		virtual char	symbol_at(size_t row, size_t column) const;

#pragma region i_symbol_getter

	public:
		virtual std::array<char, 8> get_symbol_ddram(size_t row, size_t column) const override;

#pragma endregion i_symbol_getter

	protected:
		size_t				m_width;
		size_t				m_height;
		std::vector<char>	m_visual;
		lcd_controller_wptr m_controller;
		event_t				m_on_controller_changed;
	};
} // namespace lcd