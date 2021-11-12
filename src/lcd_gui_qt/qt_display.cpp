#include <stdafx.h>

#include "qt_display.h"

#include "display_content.h"
#include "display_settings.h"
#include "pcb_graphics_settings.h"
#include "port_widget.h"

#include <qpainter>
#include <qpaintevent>
#include <qstyle>

namespace lcd
{
#define CHECK_CONTROLLER(action)                                                                                       \
	lcd_controller_ptr ctrl = m_controller.lock();                                                                     \
	if (!ctrl)                                                                                                         \
		{                                                                                                              \
			action;                                                                                                    \
		}

	constexpr float	   ce_pixel_size { 3 };
	constexpr float	   ce_pixel_spacing { .4f };
	constexpr float	   ce_char_width { 5 };
	constexpr float	   ce_char_height { 8 };
	constexpr float	   ce_char_hspacing { 6 };
	constexpr float	   ce_char_vspacing { 6 };
	constexpr QMargins ce_padding { 0, 0, 0, 0 };

	qt_display::qt_display(QWidget* parent) : QWidget(parent), display(16, 4)
	{
		QVBoxLayout* l = new QVBoxLayout();
		setLayout(l);
		on_controller_changed([ = ] {
			CHECK_CONTROLLER();
			m_port_widget = new port_widget(ctrl->m_port.m_pins.data(), ctrl->m_port.m_pins.size(), this);
			l->insertWidget(0, m_port_widget);
		});

		display_settings settings;
		settings.columns = m_width;
		settings.rows	 = m_height;
		settings.get_symbol =
			std::bind(&qt_display::get_symbol_ddram, this, std::placeholders::_1, std::placeholders::_2);
		settings.pixel_size	   = ce_pixel_size;
		settings.pixel_spacing = ce_pixel_spacing;
		settings.char_width	   = ce_char_width;
		settings.char_height   = ce_char_height;
		settings.char_hspacing = ce_char_hspacing;
		settings.char_vspacing = ce_char_vspacing;

		m_display_content_widget = new display_content_widget();
		m_display_content_widget->set_settings(settings);
		layout()->addWidget(m_display_content_widget);
		setStyleSheet(tr("background-color: %1").arg(g_pcb_graphics_settings.light_color.name()));
	}

#pragma region display

	void qt_display::update(update_reason_enum reason)
	{
		m_port_widget->update();
		QWidget::update();
	}

#pragma endregion display
} // namespace lcd
