#include <stdafx.h>

#include <logging_prototypes.h>

#include "log_history_model.h"

#include <factory/log_history_sink_factory.h>
#include <i_log_history.h>
#include <log_helper.h>
#include <log_history_sink.h>
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

	int log_history_model::columnCount(const QModelIndex& parent) const { return 3; }

	int log_history_model::rowCount(const QModelIndex& parent) const
	{
		return std::static_pointer_cast<log_history>(m_log_history)->count();
	}

	QVariant log_history_model::data(const QModelIndex& index, int role) const
	{
		switch (role)
			{
			case Qt::ItemDataRole::DecorationRole:
				if (index.column() == 1)
					return QPixmap(
						tr(":/res/icons/16/%1.png")
							.arg(to_string(*static_cast<logger::log_level*>(index.internalPointer())).c_str()));
			case Qt::ItemDataRole::DisplayRole:
				if (index.column() == 0 || index.column() == 2)
					{
						std::string& str		   = *(static_cast<std::string*>(index.internalPointer()));
						size_t		 separator_pos = str.find_first_of('|');
						std::string	 timestamp	   = str.substr(0, separator_pos);
						std::string	 message	   = str.substr(separator_pos + 1);
						switch (index.column())
							{
							case 0: return timestamp.c_str();
							case 2: return message.c_str();
							default: return {};
							}
					}
			}

		return {};
	}

	QModelIndex log_history_model::index(int row, int column, const QModelIndex& parent) const
	{
		switch (column)
			{
			case 0:
			case 2: return createIndex(row, column, std::static_pointer_cast<log_history>(m_log_history)->message(row));
			case 1: return createIndex(row, 1, std::static_pointer_cast<log_history>(m_log_history)->level(row));
			default: return QModelIndex();
			}
	}

	QModelIndex log_history_model::parent(const QModelIndex& index) const { return {}; }
} // namespace lcd
