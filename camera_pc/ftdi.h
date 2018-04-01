#include "ftd2xx.h"

// Data variable
struct FTDIData{
    unsigned char buffer[65535];
    unsigned long buff_len;
};

// Devices variable
struct FTDIDevices{
    char device1[64];
    char device2[64];
    char device3[64];
    char device4[64];
    unsigned int ndevs;
};

class ftdi
{
private:
    // Internal variables

    DWORD deviceID;

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    FT_DEVICE ftDevice;

    DWORD LatencyTimer = 100;

    UCHAR MODE_SYNC_245 = 0x40;
    UCHAR Mask = 0xFF;

public:
    ftdi();
    int ListDevices(FTDIDevices *devices);
    int Connect(char serial[]);
    int Disconnect();
    int Write(FTDIData data);
    void Purge();
    int Read(unsigned char *buffer);
    int QueryQue();
};
