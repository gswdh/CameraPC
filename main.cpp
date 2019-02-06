#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gscamera.h"
#include "stb_image_write.h"

using namespace std;

int main()
{
	// Handles
	gscamera cam;

	// Image data space
	uint8_t* image_data = (uint8_t*)malloc(3100*2200);

	// Connect to the camera
	int cam_result = cam.connect("GSW1G8LTV");
	if(cam_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;

	uint16_t res_x = 3000, res_y = 2200, int_time = 10;
	int loop = 1;

	cam.setRes(res_x, res_y);
	cam.setIntegration(int_time);

	while(loop == 1)
	{
		cam.getImage(image_data);

		stbi_write_bmp("image.png", res_y, res_x, 1, image_data);
	}
}
