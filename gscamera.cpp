#include "gscamera.h"

gscamera::gscamera()
{

}

int8_t gscamera::connect(std::string serial_n)
{
	// Result
	int8_t ft_result = -1;

	// Connect to the camera FTDI chip
	ft_result = ft.connect(serial_n);

	// Reset the camera to get into a known state
    ft_result = this->resetCam();

	// Flush the USB FIFOs
	ft_result = ft.purge();

	if(ft_result != FT_OK) return ft_result;

	// Set up the camera... TODO: document and finish
	// Sequencer
	this->setReg(0, 272);

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

    return ft_result;
}

gscamera::~gscamera()
{
 	ft.disconnect();
}

int8_t gscamera::getImage(uint8_t * pData)
{
	int8_t ft_result = -1;

	// Start a new image grab
    ft_result = this->triggerCam();

	// Constant for additional pixels
    int8_t pix_const = 0;

	// Now get the data
	ft_result = ft.receive(pData, (_res_x * _res_y) + pix_const);

	// Result
	return ft_result;
}

int8_t gscamera::setRes(uint16_t x, uint16_t y)
{
	// Update locals
	_res_x = x;
	_res_y = y;

	// Reg set result
	int8_t ft_result = -1;

	// Update the camera y res
    ft_result = this->setReg(1, ((_res_y / 2) - 1));

	// Update the camera x res
    ft_result = this->setReg(2, (_res_x - 1));

	// Return the result
	return ft_result;
}

// TODO: finish
int8_t gscamera::setGain(uint16_t gain)
{
	_gain = gain;
	return 0;
}

int8_t gscamera::setIntegration(uint16_t time)
{
	// Update local
	_int_time = time;

	// Update camera
    int ft_result = this->setReg(3, _int_time);

	// Return
	return ft_result;
}

int8_t gscamera::setSubsampling(uint16_t mode)
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
	
int8_t gscamera::setReg(uint8_t reg, uint16_t value)
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

int8_t gscamera::triggerCam()
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

int8_t gscamera::resetCam()
{

	// Return
	return 0;
}

uint16_t gscamera::getResX()
{
	return _res_x;
}

uint16_t gscamera::getResY()
{
	return _res_y;
}

uint32_t gscamera::getQueue()
{
    uint32_t bytes = 0;

    ft.getQueLen(&bytes);

    return bytes;
}
