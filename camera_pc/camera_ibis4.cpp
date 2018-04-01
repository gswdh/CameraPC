/*
 * camera_ibis4.cpp
 *
 *  Created on: 7 Jan 2018
 *      Author: George
 */

#include "camera_ibis4.h"

using namespace std;

camera_ibis4::camera_ibis4(char name[])
{
	if(ft.Connect(name) == 0)
	{
		cout << "Connected." << endl;

		// Create a sensor reset
		setReg(13, 2);
		Sleep(100);
		setReg(13, 0);

		// Sequencer
		//setReg(0, 0);

		// Y resolution (must be half required)
		setReg(1, ((image_y_res / 2) - 1));

		// X resolution
		setReg(2, (image_x_res - 1));

		// Integration time in sys clocks
		setReg(3, int_time);

		// Sequencer delays
		//setReg(4, delay_reg + 2);

		// X reg start position
		setReg(5, 0);

		// Y reg start position
		setReg(6, 0);

		// Subsampling reg
		setReg(7, (sub_smple_mode << 2) + (sub_smple_mode << 5));

		// Amplifier reg
		setReg(8, 16);

		// DAC course offset
		setReg(9, 115);

		// DAC fine offset
		setReg(10, 110);

		// DAC black level
		setReg(11, 0);

		// ADC register
		//setReg(12, 2048);

		//return 0;
	}


	else
	{
		cout << "Could not connect." << endl;

		//return 1;
	}
}

camera_ibis4::~camera_ibis4()
{
	// TODO Auto-generated destructor stub
}

camera_ibis4::setReg(int reg, int value)
{
	FTDIData cont_data;
	cont_data.buff_len = 2;

	cont_data.buffer[0] = (reg << 4) + ((value >> 8) & 0x0f);
	cont_data.buffer[1] = (value & 0xff);

	ft.Write(cont_data);
}

camera_ibis4::getImage()
{

}

