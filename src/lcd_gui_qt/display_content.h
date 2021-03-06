#pragma once

#include <QWidget>
#include <display_settings.h>

namespace lcd
{
	class display_content_widget : public QWidget
	{
	public:
		display_content_widget();

		void set_settings(display_settings const& settings);

		void on_brightness_changed(float intencity);

		void on_contrast_changed(float intencity);

	private:
		QSize calculateMinimumSize();

#pragma region QWidget

	protected:
		virtual void paintEvent(QPaintEvent* e) override;

#pragma endregion

	private:
		display_settings m_settings;
		float			 m_brightness;
		float			 m_contrast;
	};
} // namespace lcd