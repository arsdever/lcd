#pragma once

#include <qwidget>

namespace lcd
{
	class screen_border : public QWidget
	{
	public:
		screen_border(QWidget* content, QWidget* parent = nullptr);

		virtual QSize sizeHint() const override;

	protected:
		virtual void paintEvent(QPaintEvent* evt) override;

	private:
		QWidget* m_content;
	};
} // namespace lcd