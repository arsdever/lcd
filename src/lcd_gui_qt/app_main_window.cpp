#include <stdafx.h>

#include "app_main_window.h"

#include "qt_display.h"

#include <cmath>
#include <logger.h>
#include <qhboxlayout>
#include <qslider>
#include <qstatusbar>
#include <qtimer>
#include <qtoolbar>
#include <timer_helper_functions.h>

namespace lcd
{
	app_main_window::app_main_window(float		  target_fps,
									 i_timer_wptr simulation_timer,
									 qt_display*  display,
									 QWidget*	  parent)
		: QMainWindow(parent), m_simulation_timer(simulation_timer), m_fps(target_fps), m_display(display)
	{
		setCentralWidget(display);

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

		m_simulation_speed_slider = new QSlider();
		QToolBar* toolbar		  = new QToolBar();
		addToolBar(toolbar);

		toolbar->addWidget(m_simulation_speed_slider);
		m_simulation_speed_slider->setMinimum(-12);
		m_simulation_speed_slider->setMaximum(0);
		m_simulation_speed_slider->setValue(-6);
		m_simulation_speed_slider->setOrientation(Qt::Orientation::Horizontal);
		connect(m_simulation_speed_slider, &QSlider::valueChanged, this, &app_main_window::update_simulation_speed);
		update_simulation_speed();
	}

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
		if (i_timer_ptr timer = m_simulation_timer.lock())
			{
				timer->set_prescaler(pow(10, m_simulation_speed_slider->value()));
			}
	}
} // namespace lcd
