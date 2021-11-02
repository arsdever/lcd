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
		connect(m_simulation_speed_slider, &QSlider::valueChanged, this, &app_main_window::update_simulation_speed);
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
				double		elapsed = timer->elapsed().count();
				std::string suffix	= "s";
				if (elapsed < .000001)
					{
						elapsed *= 1000000000.0f;
						suffix = "ns";
					}
				else if (elapsed < .001)
					{
						elapsed *= 1000000.0f;
						suffix = "us";
					}
				else if (elapsed < 1)
					{
						elapsed *= 1000.0f;
						suffix = "ms";
					}

				sb->showMessage(tr("delta time: %1 %2 prescaler: %3")
									.arg(elapsed)
									.arg(suffix.c_str())
									.arg(pow(10, m_simulation_speed_slider->value())));
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