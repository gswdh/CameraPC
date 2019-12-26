#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ftd2xx.h"

int main()
{
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;

	ftStatus = FT_Open(0, &ftHandle);

	if(ftStatus == FT_OK)
	{
		printf("All okay\n");
	}

	else
	{
		printf("Error\n");
	}

	return 0;
}