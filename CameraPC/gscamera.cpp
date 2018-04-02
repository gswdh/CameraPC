#include "gscamera.h"

gscamera::gscamera(char serial_n[])
{
	// Result
	int ft_result = -1;

	// Connect to the camera FTDI chip
	ft_result = ft.connect(serial_n);

	// Reset the camera to get into a known state
    ft_result = this->resetCam();

	// Flush the USB FIFOs
	ft_result = ft.purge();

	// Set up the camera... TODO: document and finish
	// Sequencer
	//this.setReg(0, 272);

	// Y resolution (must be half required)
    this->setReg(1, ((_res_y / 2) - 1));

	// X resolution
    this->setReg(2, (_res_x - 1));

	// Integration time in sys clocks
    this->setReg(3, _int_time);

	// Sequencer delays
    this->setReg(4, 2);

	// X reg start position
    this->setReg(5, 0);

	// Y reg start position
    this->setReg(6, 0);

	// Subsampling reg
    this->setReg(7, (_subsample_mode << 2) + (_subsample_mode << 5));

	// Amplifier reg
    this->setReg(8, _gain);

	// DAC course offset
    this->setReg(9, 115);

	// DAC fine offset
    this->setReg(10, 110);

	// DAC black level
    this->setReg(11, 0);

	// ADC register
	//this.setReg(12, 2048);
}

gscamera::~gscamera()
{
	ft.disconnect();
}

int gscamera::getImage(unsigned char* pData)
{
	int ft_result = -1;

	// Make sure we have enough space
	image_data = (unsigned char*)realloc(image_data, (_res_x * _res_y) * sizeof(unsigned char));

	// Successful?
	if(image_data == NULL)
		return CAM_ERR;

	// Start a new image grab
    ft_result = this->triggerCam();

	// Constant for additional pixels
	int pix_const = 0;

	// Now get the data
	ft_result = ft.receive(image_data, (_res_x * _res_y) + pix_const);

	// Copy the data over
	memcpy(pData, image_data, sizeof(image_data));

	// Result
	return ft_result;
}

int gscamera::setRes(int x, int y)
{
	// Update locals
	_res_x = x;
	_res_y = y;

	// Reg set result
	int ft_result = -1;

	// Update the camera y res
    ft_result = this->setReg(1, ((_res_y / 2) - 1));

	// Update the camera x res
    ft_result = this->setReg(2, (_res_x - 1));

	// Return the result
	return ft_result;
}

// TODO: finish
int gscamera::setGain(int gain)
{
	_gain = gain;
	return 0;
}

int gscamera::setIntegration(int time)
{
	// Update local
	_int_time = time;

	// Update camera
    int ft_result = this->setReg(3, _int_time);

	// Return
	return ft_result;
}

int gscamera::setSubsampling(int mode)
{
	// Update local
	_subsample_mode = mode;

	// Result
	int ft_result = -1;

	// Update the camera
    ft_result = this->setReg(7, (_subsample_mode << 2) + (_subsample_mode << 5));

	// Return 
	return ft_result;
}
	
int gscamera::setReg(int reg, int value)
{
	// Create a buffer to pass to the ft object
	unsigned char txBuffer[2];

	// Format the data
	txBuffer[0] = (reg << 4) + ((value >> 8) & 0x0f);
	txBuffer[1] = (value & 0xff);

	// Send the data
	int ft_result = ft.transmit(txBuffer, 2);

	// Return the error
	return ft_result;
}

int gscamera::triggerCam()
{
	// Result
	int ft_result = -1;

	// Reset the reg to create a rising edge
    ft_result = this->setReg(13, 0);

	// Create a rising edge
    ft_result = this->setReg(13, 1);

	// Reset the reg
    ft_result = this->setReg(13, 0);

	// Return
	return ft_result;
}

int gscamera::resetCam()
{
	// Result
	int ft_result = -1;

	// Set reg for going into and out of reset
    ft_result = this->setReg(13, 2);
    usleep(100000);
    ft_result = this->setReg(13, 0);

	// Return
	return ft_result;
}

int gscamera::getResX()
{
	return _res_x;
}

int gscamera::getResY()
{
	return _res_y;
}

int gscamera::getQueue()
{
    unsigned long bytes = 0;

    ft.getQueLen(&bytes);

    return bytes;
}
