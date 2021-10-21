#include <stdafx.h>

#include "app_main_window.h"

#include "qt_display.h"

#include <logger.h>
#include <qstatusbar>
#include <qtimer>

namespace lcd
{
	app_main_window::app_main_window(float		  target_fps,
									 i_timer_wptr simulation_timer,
									 qt_display*  display,
									 QWidget*	  parent)
		: QMainWindow(parent), m_simulation_timer(simulation_timer), m_fps(target_fps), m_display(display)
	{
		display->setParent(this);
		display->move(0, 0);

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

				sb->showMessage(tr("delta time: %1 %2").arg(elapsed).arg(suffix.c_str()));
			}
	}
} // namespace lcd