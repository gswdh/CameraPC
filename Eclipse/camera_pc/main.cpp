#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gscamera.h"


using namespace std;

int main()
{
	gscamera cam;
	ofstream myfile;

	int cam_result = cam.connect("GSW1G8LTV");

	if(cam_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;


	int res_x = 100, res_y = 100;

	int loop = 1;

	while(loop)
	{

		cam.setRes(res_x, res_y);

		unsigned char* image_data = (unsigned char*)malloc(res_x * res_y);

		cam.getImage(image_data);

		myfile.open("image.pgm");
		myfile << "P2\n" << res_y << " " << res_x << "\n" << "255" << endl;

		for(unsigned long i = 0; i < (res_x * res_y); i++)
		{
			myfile << (int)*image_data << endl;
			image_data++;
		}
		myfile.close();
	}


	/*
	ftdi ft;

	int ft_result = ft.connect("GSW1G8LTV");

	if(ft_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;

	ft.disconnect();

*/





}
