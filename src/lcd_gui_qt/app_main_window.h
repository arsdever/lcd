#pragma once

#include <i_timer.h>
#include <qmainwindow>

class QTimer;
class QSlider;

namespace lcd
{
	class qt_display;

	class app_main_window : public QMainWindow
	{
		Q_OBJECT

	public:
		using slider_change_callback_t = std::function<void(float)>;

	public:
		app_main_window(float target_fps, i_timer_wptr simulation_timer, QWidget* parent = nullptr);
		virtual ~app_main_window() override;

		void on_brightness_slider(slider_change_callback_t cb);
		void on_contrast_slider(slider_change_callback_t cb);

	private slots:
		void update_status_bar();
		void update_simulation_speed();

	private:
		QMetaObject::Connection	 m_status_bar_update_connection;
		i_timer_wptr			 m_simulation_timer;
		QTimer*					 m_fps_timer;
		QSlider*				 m_simulation_speed_slider;
		QSlider*				 m_brightness_slider;
		QSlider*				 m_contrast_slider;
		slider_change_callback_t m_brightness_slider_cb;
		slider_change_callback_t m_contrast_slider_cb;
		float					 m_fps;
		std::thread				 m_scheduler_thread;
		bool					 m_stop_flag;
	};
} // namespace lcd