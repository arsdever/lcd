#pragma once

namespace lcd
{
	class log_history_model : public QAbstractItemModel
	{
	public:
		log_history_model();

#pragma region QAbstractItemModel

		virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

		virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

		virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

		virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

		virtual QModelIndex parent(const QModelIndex& index) const override;

#pragma endregion

	private:
		log_history_ptr m_log_history;
	};
} // namespace lcd