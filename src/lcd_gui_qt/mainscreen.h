#pragma once

#include <qopenglwidget.h>

namespace carui
{
	class mainscreen : public QOpenGLWidget
	{
		Q_OBJECT

	public:
		mainscreen(QWidget* parent);
	};
}