#pragma once

class QAbstractItemView;
class QAbstractItemModel;

namespace lcd
{
	class log_widget : public QWidget
	{
		Q_OBJECT

	public:
		log_widget(QWidget* parent = nullptr);

	private:
		QAbstractItemView*	m_content;
		QAbstractItemModel* m_history_model;
	};
} // namespace lcd