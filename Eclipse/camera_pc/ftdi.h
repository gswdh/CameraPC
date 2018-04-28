#include "ftd2xx.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <iostream>

#define FTDI_OK 0
#define FTDI_ERR -1

class ftdi
{
private:

    // Internal variables
    DWORD deviceID;

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    FT_DEVICE ftDevice;

    DWORD LatencyTimer;
    UCHAR MODE_SYNC_245;
    UCHAR Mask;

public:
    ftdi();
    int connect(std::string serial);
    int disconnect();
    int transmit(unsigned char* txBuffer, long long nBytes);
    int purge();
    int receive(unsigned char* rxBuffer, long long nBytes);
    int getQueLen(unsigned long * nBytes);
    ~ftdi();
};
