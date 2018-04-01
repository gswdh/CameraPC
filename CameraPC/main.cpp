#include <QtGui>
#include <QApplication>
#include <QLabel>

#include "ftdi.h"

int main(int argc, char **argv) 
{

	ftdi ft;

	QApplication app(argc, argv);

	char serial_number[] = {"GSW1G8LTV"};

	QString message;

	if(ft.connect(serial_number) == FTDI_OK)
	{
		message = "Connected!";
	}

	else 
	{
		message = "Couldn't :(";
	}

	ft.disconnect();

	QLabel label(message);
	label.show();

	return app.exec();
}