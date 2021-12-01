#include <stdafx.h>

#include <logging_prototypes.h>

#include "log_history_model.h"

#include <factory/log_history_sink_factory.h>
#include <log_history_sink.h>
#include <i_log_history.h>
#include <log_helper.h>
#include <logging/log_history.h>

namespace lcd
{
	log_history_model::log_history_model() : m_log_history(std::make_shared<log_history>())
	{
		std::shared_ptr<log_history_sink> sink = log_history_sink_factory::create(m_log_history);
		logger::add_sink(sink);
		std::shared_ptr<log_history> history = std::static_pointer_cast<log_history>(m_log_history);
		history->on_updated(
			[ this, history ] { beginInsertRows({}, rowCount() - 1, rowCount() - 1), endInsertRows(); });
	}

	int log_history_model::columnCount(const QModelIndex& parent) const { return 2; }

	int log_history_model::rowCount(const QModelIndex& parent) const
	{
		return std::static_pointer_cast<log_history>(m_log_history)->count();
	}

	QVariant log_history_model::data(const QModelIndex& index, int role) const
	{
		switch (role)
			{
			case Qt::ItemDataRole::DecorationRole:
				if (!index.column())
					return QPixmap(
						tr(":/res/icons/16/%1.png")
							.arg(to_string(*static_cast<logger::log_level*>(index.internalPointer())).c_str()));
			case Qt::ItemDataRole::DisplayRole:
				if (index.column())
					return QString(static_cast<std::string*>(index.internalPointer())->c_str());
			}

		return {};
	}

	QModelIndex log_history_model::index(int row, int column, const QModelIndex& parent) const
	{
		if (!column)
			return createIndex(row, 0, std::static_pointer_cast<log_history>(m_log_history)->level(row));
		else
			return createIndex(row, 1, std::static_pointer_cast<log_history>(m_log_history)->message(row));
	}

	QModelIndex log_history_model::parent(const QModelIndex& index) const { return {}; }
} // namespace lcd
