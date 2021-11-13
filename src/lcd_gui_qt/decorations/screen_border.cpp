#include <stdafx.h>

#include "screen_border.h"

namespace lcd
{
	namespace
	{
		static constexpr int horizontal_margin = 30;
		static constexpr int vertical_margin   = 16;
	} // namespace

	screen_border::screen_border(QWidget* content, QWidget* parent) : QWidget(parent), m_content(content)
	{
		m_content->setParent(this);
		m_content->move(horizontal_margin, vertical_margin);
		setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		setContentsMargins(horizontal_margin, vertical_margin, horizontal_margin, vertical_margin);
	}

	QSize screen_border::sizeHint() const
	{
		return QSize(2 * horizontal_margin + m_content->width(), 2 * vertical_margin + m_content->height());
	}

	void screen_border::paintEvent(QPaintEvent* evt)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.fillRect(evt->rect(), QColor("#323232"));
	}
} // namespace lcd