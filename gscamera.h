#include "ftdiwrapper/inc/ftdi.h"
#include "gsbus.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CAM_OK 0
#define CAM_ERR -1

// Registers for the GSBus interface
#define GS_GPREG	0 // General purpose reg is always 0
#define CAM_SPI_REG	1
#define CAM_CNT_REG	2


class gscamera
{

private:
	// Varibale to communicate with the camera
	ftdi ft;

	// Camera settings
	uint16_t _res_x = 640;
	uint16_t _res_y = 480;
	uint16_t _gain = 0;
	uint16_t _int_time = 100;
	uint16_t _subsample_mode = 0;

	// Change the camera settings
	int8_t setReg(uint8_t reg, uint16_t value);
	int8_t resetCam();

public:
    gscamera();
    int8_t triggerCam();
    int8_t connect(std::string serial_n);
    int8_t getImage(uint8_t * pData);
    int8_t setRes(uint16_t x, uint16_t y);
    int8_t setGain(uint16_t gain);
    int8_t setIntegration(uint16_t time);
	int8_t setSubsampling(uint16_t mode);
	uint16_t getResX();
	uint16_t getResY();
	uint32_t getQueue();
    ~gscamera();
};
