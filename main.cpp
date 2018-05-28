#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gscamera.h"

using namespace std;

int main()
{
	// Handles
	gscamera cam;
	FILE* pFile;

	// Image data space
	uint8_t* image_data = (uint8_t*)malloc(3100*2200);

	// Connect to the camera
	int cam_result = cam.connect("GSW1G8LTV");
	if(cam_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;

	// Create the image file and header
	char buffer [50];

	uint16_t res_x = 3000, res_y = 2000, int_time = 100;
	uint32_t average = 0, max_exp = 0, min_exp = 255;
	int loop = 1;

	while(loop == 1)
	{
		cam.setRes(res_x, res_y);
		cam.setIntegration(int_time);

		cam.getImage(image_data);

		for(uint32_t i = 0; i < (cam.getResY() * cam.getResX()); i++)
		{
			// Make the average
			average = average + image_data[i];

			// Get the minimum
			if(image_data[i] < min_exp) min_exp = image_data[i];

			// Get the maximum
			if(image_data[i] > max_exp) max_exp = image_data[i];
		}

		cout << "Exposure level = " << average / (cam.getResY() * cam.getResX()) << endl;
		cout << "Max level = " << max_exp << endl;
		cout << "Min level = " << min_exp << endl;

		average = 0;
		max_exp = 0;
		min_exp = 255;


		uint8_t bytes = sprintf(buffer, "P5 %d %d 255 \n", cam.getResY(), cam.getResX());
		pFile = fopen("image.pgm", "wb");
		fwrite(buffer, 1, bytes*sizeof(uint8_t), pFile);
		fwrite(image_data, 1, cam.getResX()*cam.getResY()*sizeof(uint8_t), pFile);
		fclose(pFile);
	}
}
