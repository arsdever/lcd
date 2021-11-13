#pragma once

#include <display.h>
#include <i_timer.h>
#include <qwidget.h>

namespace lcd
{
	class port_widget;
	class display_content_widget;

	class qt_display
		: public QWidget
		, public display
	{
		Q_OBJECT

	public:
		qt_display(QWidget* parent = nullptr);

#pragma region QWidget

	protected:
		virtual void paintEvent(QPaintEvent* e) override;
		virtual void mousePressEvent(QMouseEvent* e) override;
		virtual void mouseMoveEvent(QMouseEvent* e) override;
		virtual void mouseReleaseEvent(QMouseEvent* e) override;

#pragma endregion

#pragma region display

	public:
		virtual void update(update_reason_enum reason) override;

#pragma endregion display

	private:
		display_content_widget* m_display_content_widget;
		port_widget*			m_port_widget;
		QWidget*				m_display_with_decorations;
		QPoint					m_delta_pos;
	};
} // namespace lcd