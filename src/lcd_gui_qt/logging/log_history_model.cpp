#include <stdafx.h>

#include <logging_prototypes.h>

#include "log_history_model.h"

#include <log_history.h>

namespace lcd
{
	log_history_model::log_history_model() : m_log_history(std::make_shared<log_history>()) { }

	int log_history_model::columnCount(const QModelIndex& parent) const { return {}; }

	QVariant log_history_model::data(const QModelIndex& index, int role) const { return {}; }

	QModelIndex log_history_model::index(int row, int column, const QModelIndex& parent) const { return {}; }

	QModelIndex log_history_model::parent(const QModelIndex& index) const { return {}; }

	int log_history_model::rowCount(const QModelIndex& parent) const { return {}; }
} // namespace lcd
