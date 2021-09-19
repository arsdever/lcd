#pragma once

#include <qwidget.h>
#include <display.h>
#include <i_lcd_drawer.h>

namespace lcd
{
	class qt_display : public QWidget, public display
	{
		Q_OBJECT

	public:
		qt_display(QWidget* parent = nullptr);

#pragma region QWidget

	protected:
		void paintEvent(QPaintEvent* e) override;

#pragma endregion QWidget

#pragma region display

		virtual void update() override;

#pragma endregion display

	private:
		std::vector<i_lcd_drawer_ptr> m_drawers;
	};
}