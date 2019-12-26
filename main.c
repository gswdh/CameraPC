#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include "ftd2xx.h"

int main()
{
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;
	FT_DEVICE ftDevice;

	DWORD deviceID;
	char SerialNumber[16];
	char Description[64];

	ftStatus = FT_Open(0, &ftHandle);

	if(ftStatus == FT_OK)
	{
		ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceID, SerialNumber, Description, NULL);

		printf("Description: %s\n", Description);
		printf("Serial Number: %s\n", SerialNumber);
	}

	else
	{
		printf("Error\n");
	}


	Sleep(10000);

	FT_Close(ftHandle);

	return 0;
}
