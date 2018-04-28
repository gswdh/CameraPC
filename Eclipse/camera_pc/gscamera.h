#include "ftdi.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CAM_OK 0
#define CAM_ERR -1

class gscamera
{

private:
	// Varibale to communicate with the camera
	ftdi ft;

	// Camera settings
	int _res_x = 640;
	int _res_y = 480;
	int _gain = 0;
	int _int_time = 100;
	int _subsample_mode = 0;

	// Space for the image result
	unsigned char* image_data = NULL;

	// Change the camera settings
	int setReg(int reg, int value);

	int resetCam();

public:
    gscamera();
    int triggerCam();
    int connect(std::string serial_n);
    int getImage(unsigned char* pData);
	int setRes(int x, int y);
	int setGain(int gain);
	int setIntegration(int time);
	int setSubsampling(int mode);
	int getResX();
	int getResY();
    int getQueue();
    ~gscamera();
};
