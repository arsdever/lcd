#include <stdafx.h>

#include "qt_display.h"

#include "decorations/screen_border.h"
#include "display_content.h"
#include "display_settings.h"
#include "lcd_controller.h"
#include "pcb_graphics_settings.h"
#include "port_widget.h"

#define max(a, b)	   (((a) > (b)) ? (a) : (b))
#define min(a, b)	   (((a) < (b)) ? (a) : (b))
#define clamp(a, b, c) (min(max(a, b), c))

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

			ctrl->m_port.m_pins[ static_cast<int>(lcd_controller::pinout::v0) ].register_to_event(
				pin::event_types_enum::on_voltage_changed, [ = ] {
					m_display_content_widget->on_contrast_changed(
						ctrl->m_port.m_pins[ static_cast<int>(lcd_controller::pinout::v0) ].get_voltage() / 5.0f);
				});
			auto adjust_brightness = [ = ] {
				float anode	 = ctrl->m_port.m_pins[ static_cast<int>(lcd_controller::pinout::anode) ].get_voltage();
				float catode = ctrl->m_port.m_pins[ static_cast<int>(lcd_controller::pinout::catode) ].get_voltage();

				float diff = anode - catode;
				m_display_content_widget->on_brightness_changed(clamp(diff / 5.0f, 0, 1));
			};
			ctrl->m_port.m_pins[ static_cast<int>(lcd_controller::pinout::anode) ].register_to_event(
				pin::event_types_enum::on_voltage_changed, adjust_brightness);
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
		m_display_with_decorations = new screen_border(m_display_content_widget);
		layout()->addWidget(m_display_with_decorations);
		setWindowFlags(Qt::FramelessWindowHint);
	}

#pragma region QWidget

	void qt_display::paintEvent(QPaintEvent* e)
	{
		// draw decorations
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.fillRect(e->rect(), QBrush(g_pcb_graphics_settings.light_color));
		QWidget::paintEvent(e);
	}

	void qt_display::mousePressEvent(QMouseEvent* e)
	{
		setMouseTracking(true);
		m_delta_pos = QPoint(e->localPos().x(), e->localPos().y());
		e->accept();
	}

	void qt_display::mouseMoveEvent(QMouseEvent* e)
	{
		QPoint pos = e->globalPos() - m_delta_pos;
		move(pos);
		e->accept();
	}

	void qt_display::mouseReleaseEvent(QMouseEvent* e)
	{
		setMouseTracking(false);
		e->accept();
	}

#pragma endregion

#pragma region display

	void qt_display::update(update_reason_enum reason)
	{
		m_port_widget->update();
		QWidget::update();
	}

#pragma endregion display
} // namespace lcd
