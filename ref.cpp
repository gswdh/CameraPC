// Includes
#include "ftdi.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <Windows.h>

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

// Name space
using namespace std;
//using namespace cv;

// New FTDI object
ftdi ft;

// Image settings
const int image_y_res = 640;
const int image_x_res = 480;
unsigned long image_res = image_x_res * image_y_res;
int 		sub_smple_mode = 3,
			gain = 16,
			int_time = 10,
			delay_reg = 0;

vector<unsigned char> buffer(image_res);
vector<unsigned char> raw(65536);

//void CamSetReg(int reg, int value);
//void PrintImage(vector<unsigned char> buffer, bool scale, bool rotate);
//void GetImage(vector<unsigned char> buffer);
//int Connect();

int main(void)
{
	//if(Connect() == 0)
	if(1)
	{
		//30600
		while(1)
		{
			// Get a new image
			//GetImage(buffer);


			//duration = (clock() - start) / (double) CLOCKS_PER_SEC;
			//cout << "FPS: " << 1/duration << endl;
			//start = clock();

			// Print the image
			//PrintImage(buffer, false, false);


			/*
			// Save the image
			if(GetAsyncKeyState(VK_SPACE))
			{
				//cv::imwrite("self.bmp", image);

				cout << "Picture taken." << endl;
			}
			*/

		}
		ft.Disconnect();
	}

	else cout << "Could not connect!" << endl;

	return 0;
}
/*
void CamSetReg(int reg, int value)
{
	FTDIData cont_data;
	cont_data.buff_len = 2;

	cont_data.buffer[0] = (reg << 4) + ((value >> 8) & 0x0f);
	cont_data.buffer[1] = (value & 0xff);

	ft.Write(cont_data);
}


void PrintImage(vector<unsigned char> buffer, bool scale, bool rotate)
{
	// Convert to a mat object
	cv::Mat image(image_x_res, image_y_res, CV_8U, (uchar*)buffer.data());
	image = image.clone();

	// Rotate?
	if(rotate)
		cv::rotate(image, image, 0);

	// Scale?
	if(scale)
	{
		cv::Mat scaled(image_x_res/4, image_y_res/4, CV_8U);
		cv::resize(image, scaled, cv::Size(), 0.25, 0.25);
		cv::imshow("Image", scaled);
	}

	// Don't scale
	else
		cv::imshow("Image", image);

	// Show on the screen
	cv::waitKey(1);
}

void GetImage(vector<unsigned char> buffer)
{
	ft.Purge();

	CamSetReg(13, 1);
	CamSetReg(13, 0);

	// Local variables
	int nbytes = 0;
	unsigned long pix_cnt = 0;
	int timeout = 0;

	while(pix_cnt != image_res)
	{
		Sleep(1);

		nbytes = ft.Read(raw.data());

		if(nbytes == 0)
		{
			if(timeout == 1000)
			{
				timeout = 0;
				break;
			}

			else timeout++;
		}

		else timeout = 0;

		buffer.insert(buffer.begin() + pix_cnt, raw.begin(), raw.begin() + nbytes);

		pix_cnt += nbytes;
	}
}

int Connect()
{
	// Connect to the camera
	char name[] = {"GSW1G8LTV"};

	if(ft.Connect(name) == 0)
	{
		cout << "Connected." << endl;

		// Create a sensor reset
		CamSetReg(13, 2);
		Sleep(100);
		CamSetReg(13, 0);

		// Sequencer
		//CamSetReg(0, 272);

		// Y resolution (must be half required)
		CamSetReg(1, ((image_y_res / 2) - 1));

		// X resolution
		CamSetReg(2, (image_x_res - 1));

		// Integration time in sys clocks
		CamSetReg(3, int_time);

		// Sequencer delays
		CamSetReg(4, delay_reg + 2);

		// X reg start position
		CamSetReg(5, 0);

		// Y reg start position
		CamSetReg(6, 0);

		// Subsampling reg
		CamSetReg(7, (sub_smple_mode << 2) + (sub_smple_mode << 5));

		// Amplifier reg
		CamSetReg(8, gain);

		// DAC course offset
		CamSetReg(9, 115);

		// DAC fine offset
		CamSetReg(10, 110);

		// DAC black level
		CamSetReg(11, 0);

		// ADC register
		//CamSetReg(12, 2048);

		return 0;
	}

	else return -1;
}
*/
