#pragma once

namespace lcd
{
	class log_widget : public QWidget
	{
		Q_OBJECT

	public:
		log_widget(QWidget* parent = nullptr);

	private:
		QListView* m_content;
	};
} // namespace lcd