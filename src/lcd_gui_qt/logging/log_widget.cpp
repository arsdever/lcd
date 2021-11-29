#include <stdafx.h>

#include <logging_prototypes.h>

#include "log_widget.h"

#include "log_history_model.h"

#include <log_history.h>

namespace lcd
{
	log_widget::log_widget(QWidget* parent) : QWidget(parent)
	{
		setWindowFlag(Qt::Popup);
		m_content = new QListView(this);
		m_content->setModel(new log_history_model());
	}
} // namespace lcd
