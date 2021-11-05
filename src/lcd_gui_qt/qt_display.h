#pragma once

#include <display.h>
#include <i_lcd_drawer.h>
#include <i_timer.h>
#include <qwidget.h>

namespace lcd
{
	class qt_display
		: public QWidget
		, public display
	{
		Q_OBJECT

	public:
		qt_display(QWidget* parent = nullptr);

#pragma region QWidget
		virtual QSize minimumSizeHint() const override;

	protected:
		void paintEvent(QPaintEvent* e) override;

#pragma endregion QWidget

#pragma region display

		virtual void update(update_reason_enum reason) override;

#pragma endregion display

	private:
		std::vector<i_lcd_drawer_ptr> m_drawers;
	};
} // namespace lcd