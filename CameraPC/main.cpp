#include <QtGui>
#include <QApplication>
#include <QLabel>

#include "gscamera.h"

#include <iostream>

int main(int argc, char **argv) 
{
    char serial[] = {"GSW1G8LTV"};
    gscamera* cam = new gscamera(serial);

    unsigned char *image = (unsigned char*)malloc(cam->getResX() * cam->getResY() * 2);
    int ft_result = cam->setRes(100, 100);
    ft_result = cam->getImage(image);

    usleep(1000000);

    std::cout << cam->getQueue() << std::endl;

    delete cam;
    /*

	QApplication app(argc, argv);

    QString label_name;

    if(ft_result == 0) label_name = "Success";
    else label_name = "Failed";

    QLabel label(label_name);
    label.setFixedSize(200, 100);
	label.show();

	return app.exec();
    */
}
