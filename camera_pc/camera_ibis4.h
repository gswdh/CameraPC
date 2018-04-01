/*
 * camera_ibis4.h
 *
 *  Created on: 7 Jan 2018
 *      Author: George
 */

#ifndef CAMERA_IBIS4_H_
#define CAMERA_IBIS4_H_

#include "ftdi.h"
#include <vector>
#include <iostream>

class camera_ibis4 
{
	public:
		camera_ibis4(char name[]);
		virtual ~camera_ibis4();
		getImage();

	private:
		// 
		ftdi ft;

		// Default values
		int image_y_res = 480;
		int image_x_res = 640;
		int sub_smple_mode = 3;
		int int_time = 100;
		int gain = 16;



		setReg(int reg, int value);



};

#endif /* CAMERA_IBIS4_H_ */
