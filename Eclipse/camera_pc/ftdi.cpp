#include "ftdi.h"

ftdi::ftdi()
{
    LatencyTimer = 100;
    MODE_SYNC_245 = 0x40;
    Mask = 0xFF;
}

int ftdi::connect(std::string serial)
{

	// Convert the String to char
	int n = serial.length();

	// declaring character array
	char char_array[n+1];

	// Copying the contents of the string to char array
	strcpy(char_array, serial.c_str());

    // Open the FTDI device with the spcified serial number
    ftStatus = FT_OpenEx(char_array, FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

    // Reset the FTDI device
    ftStatus = FT_SetBitMode(ftHandle, Mask, 0);

    // Delay for the device to restart
    //usleep(100000);


    // Set the mode to 245 sync
    ftStatus = FT_SetBitMode(ftHandle, Mask, MODE_SYNC_245);

    // Configure latency
    ftStatus = FT_SetLatencyTimer(ftHandle, LatencyTimer);

    // Configure USB params
    ftStatus = FT_SetUSBParameters(ftHandle, 32768, 0);

    // Set the flow control
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);

    // Start with clear buffers
    int ft_result = this->purge();

    // Return
    if((ftStatus == FT_OK) & (ft_result == FTDI_OK))
        return FTDI_OK;
    else
        return FTDI_ERR;
}

int ftdi::disconnect()
{
	// Nothing was connected in the first place
    if(ftHandle == NULL)return FTDI_ERR;

    // Close
    else FT_Close(&ftHandle);

    // All done okay
    return FTDI_OK;
}

int ftdi::transmit(unsigned char* txBuffer, long long nBytes)
{
    // Check how many bytes are written
    DWORD nBytesWritten = 0, txBytes = 0;

    // If the device hasn't been connected to yet
    if(ftHandle == NULL)
        return FTDI_ERR;

    // If good, proceed
    else 
    {
        // Go through all the data
        while(nBytes > 0)
        {
        	// Create the packet size
        	if(nBytes > 65535)txBytes = 65535;
        	else txBytes = nBytes;

			// Write as much data as possible
			ftStatus = FT_Write(ftHandle, txBuffer, txBytes, &nBytesWritten);

			// Increment the pointer by the number of bytes successfully written
			txBuffer += nBytesWritten;

			// Decrement the bytes counter
			nBytes -= nBytesWritten;
        }   
        return FTDI_OK;
    }
}

int ftdi::purge()
{
    // Get rid of stale data
    ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);

    // Return
    if(ftStatus == FT_OK)
        return FTDI_OK;
    else
        return FTDI_ERR;
}

int ftdi::receive(unsigned char* rxBuffer, long long nBytes)
{
	// Check how many bytes are written
    DWORD nBytesRead = 0, rxBytes = 0;

    // If the device hasn't been connected to yet
    if(ftHandle == NULL)
        return FTDI_ERR;

    // If good, proceed
    else 
    {
        // Go through all the data
        while(nBytes > 0)
        {
        	// Get the number of bytes available
			FT_GetQueueStatus(ftHandle, &rxBytes);

			// Write as much data as possible
			ftStatus = FT_Read(ftHandle, rxBuffer, rxBytes, &nBytesRead);

			// Return
			if(ftStatus != FT_OK)
				return FTDI_ERR;

			// Increment the pointer by the number of bytes successfully written
			rxBuffer += nBytesRead;

			// Decrement the bytes counter
			nBytes -= nBytesRead;
        }   

        return FTDI_OK;
    }   
}

int ftdi::getQueLen(unsigned long * nBytes)
{
    DWORD RxBytes;

    // Get the number of bytes in the queue to be read
    ftStatus = FT_GetQueueStatus(ftHandle, &RxBytes);

    // Write the value back
    *nBytes = (unsigned long)RxBytes;

    // Return
    if(ftStatus == FT_OK)
        return FTDI_OK;
    else
        return FTDI_ERR;
}

ftdi::~ftdi()
{
    this->disconnect();
}
