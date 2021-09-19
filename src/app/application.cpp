#include "stdafx.h"

#include <lcd_widget.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	lcd::lcd_widget panel(nullptr);
	panel.show();

	app.exec();
}
