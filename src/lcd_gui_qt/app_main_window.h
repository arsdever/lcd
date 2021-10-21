#pragma once

#include <i_timer.h>
#include <qmainwindow>

class QTimer;

namespace lcd
{
	class qt_display;

	class app_main_window : public QMainWindow
	{
		Q_OBJECT

	public:
		app_main_window(float		 target_fps,
						i_timer_wptr simulation_timer,
						qt_display*	 display,
						QWidget*	 parent = nullptr);

	private slots:
		void update_status_bar();

	private:
		QMetaObject::Connection m_status_bar_update_connection;
		i_timer_wptr			m_simulation_timer;
		QTimer*					m_fps_timer;
		qt_display*				m_display;
		float					m_fps;
	};
} // namespace lcd