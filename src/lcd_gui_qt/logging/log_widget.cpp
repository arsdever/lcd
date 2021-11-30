#include <stdafx.h>

#include <logging_prototypes.h>

#include "log_widget.h"

#include "log_history_model.h"

#include <i_log_history.h>
#include <qtableview>

namespace lcd
{
	log_widget::log_widget(QWidget* parent) : QWidget(parent)
	{
		m_history_model = new log_history_model();
		m_content		= new QTableView();
		m_content->setModel(m_history_model);
		setLayout(new QVBoxLayout());
		layout()->addWidget(m_content);
		resize(400, 200);
	}
} // namespace lcd
