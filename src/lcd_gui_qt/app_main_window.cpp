#include <stdafx.h>

#include "app_main_window.h"

#include "pcb_graphics_settings.h"
#include "qt_display.h"

#include <cmath>
#include <logger.h>
#include <qhboxlayout>
#include <qslider>
#include <qstatusbar>
#include <qtimer>
#include <qtoolbar>
#include <qtoolbutton>
#include <scheduler.h>
#include <timer_helper_functions.h>

lcd::scheduler g_scheduler;

namespace lcd
{
	app_main_window::app_main_window(float target_fps, timer_wptr simulation_timer, QWidget* parent)
		: QMainWindow(parent), m_simulation_timer(simulation_timer), m_fps(target_fps)
	{
		g_scheduler.set_timer(m_simulation_timer);
		m_fps_timer = new QTimer();

		float interval_per_frame = 1000.0 / target_fps;
		m_fps_timer->setInterval(std::chrono::milliseconds(static_cast<int>(interval_per_frame)));
		QMetaObject::Connection connection =
			connect(m_fps_timer, &QTimer::timeout, this, &app_main_window::update_status_bar);

		QStatusBar* sb = statusBar();
		if (sb == nullptr)
			{
				sb = new QStatusBar {};
				setStatusBar(sb);
			}

		m_fps_timer->start();

		m_simulation_speed_slider  = new QSlider();
		QToolBar*	 toolbar	   = new QToolBar();
		QToolBar*	 timer_toolbar = new QToolBar();
		QToolButton* play_button   = new QToolButton();
		QToolButton* step_button   = new QToolButton();
		QToolButton* stop_button   = new QToolButton();

		play_button->setIcon(QIcon(":/res/icons/16/play.png"));
		step_button->setIcon(QIcon(":/res/icons/16/step.png"));
		stop_button->setIcon(QIcon(":/res/icons/16/stop.png"));

		addToolBar(timer_toolbar);
		addToolBar(toolbar);

		timer_toolbar->addWidget(play_button);
		timer_toolbar->addWidget(step_button);
		timer_toolbar->addWidget(stop_button);
		timer_toolbar->addWidget(m_simulation_speed_slider);

		m_simulation_speed_slider->setMinimum(-20);
		m_simulation_speed_slider->setMaximum(0);
		m_simulation_speed_slider->setValue(-5);
		m_simulation_speed_slider->setOrientation(Qt::Orientation::Horizontal);
		connect(m_simulation_speed_slider, &QSlider::valueChanged, this, &app_main_window::update_simulation_speed);
		update_simulation_speed();
		setAutoFillBackground(true);
		setStyleSheet(tr("background-color: %1").arg(g_pcb_graphics_settings.light_color.name()));

		m_brightness_slider = new QSlider();
		m_brightness_slider->setMinimum(0);
		m_brightness_slider->setMaximum(100);
		m_brightness_slider->setValue(100);
		m_brightness_slider->setOrientation(Qt::Orientation::Horizontal);

		m_contrast_slider = new QSlider();
		m_contrast_slider->setMinimum(0);
		m_contrast_slider->setMaximum(100);
		m_contrast_slider->setValue(100);
		m_contrast_slider->setOrientation(Qt::Orientation::Horizontal);

		connect(m_brightness_slider, &QSlider::valueChanged, this, [ = ](int value) {
			m_brightness_slider_cb ? m_brightness_slider_cb(value / 100.0f) : void();
		});
		connect(m_contrast_slider, &QSlider::valueChanged, this, [ = ](int value) {
			m_contrast_slider_cb ? m_contrast_slider_cb(value / 100.0f) : void();
		});

		toolbar->setOrientation(Qt::Vertical);
		toolbar->addWidget(m_brightness_slider);
		toolbar->addWidget(m_contrast_slider);

		connect(play_button, &QToolButton::clicked, this, [ play_button ] {
			if (g_scheduler.get_state() == scheduler::state::running)
				{
					g_scheduler.pause();
					play_button->setIcon(QIcon(":/res/icons/16/play.png"));
				}
			else
				{
					g_scheduler.run();
					play_button->setIcon(QIcon(":/res/icons/16/pause.png"));
				}
		});
		connect(step_button, &QToolButton::clicked, this, [] { g_scheduler.tick(); });
		g_scheduler.pause();
		g_scheduler.start();
	}

	void app_main_window::on_brightness_slider(slider_change_callback_t cb) { m_brightness_slider_cb = cb; }

	void app_main_window::on_contrast_slider(slider_change_callback_t cb) { m_contrast_slider_cb = cb; }

	void app_main_window::update_status_bar()
	{
		QStatusBar* sb = statusBar();
		if (sb == nullptr)
			{
				logger::warn("Status bar is not initialized");
				disconnect(m_status_bar_update_connection);
				return;
			}

		if (auto timer = m_simulation_timer.lock())
			{
				double elapsed = timer->elapsed().count();

				sb->showMessage(tr("delta time: %1 prescaler: %2")
									.arg(time_string(elapsed).c_str())
									.arg(time_string(pow(10, m_simulation_speed_slider->value()), 1).c_str()));
			}
	}

	void app_main_window::update_simulation_speed()
	{
		if (timer_ptr timer = m_simulation_timer.lock())
			{
				timer->set_prescaler(pow(10, m_simulation_speed_slider->value()));
			}
	}
} // namespace lcd
