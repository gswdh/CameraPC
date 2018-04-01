#include <QtGui>
#include <QApplication>
#include <QLabel>

#include "gscamera.h"

int main(int argc, char **argv) 
{
    gscamera cam;

    QString label_name;

    if(cam.start("GSW1G8LTV") == 0)
        label_name = "Connected";
    else
        label_name = "Not connected";

    //unsigned char *image = (unsigned char*)malloc(cam.getResX() * cam.getResY() * 2);

    //cam.getImage(image);


	QApplication app(argc, argv);

    QLabel label(label_name);
	label.show();

	return app.exec();
}
