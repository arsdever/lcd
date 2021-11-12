#pragma once

#include <display_settings.h>
#include <qwidget>

namespace lcd
{
	class display_content_widget : public QWidget
	{
	public:
		display_content_widget();

		void set_settings(display_settings const& settings);

	private:
		QSize calculateMinimumSize();

#pragma region QWidget

	protected:
		virtual void paintEvent(QPaintEvent* e) override;

#pragma endregion

	private:
		display_settings m_settings;
	};
} // namespace lcd