#include "ftd2xx.h"
#include <unistd.h>

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

    DWORD const LatencyTimer = 100;
    UCHAR const MODE_SYNC_245 = 0x40;
    UCHAR const Mask = 0xFF;

public:
    ftdi();
    int connect(char serial_n[]);
    int disconnect();
    int transmit(unsigned char* txBuffer, unsigned long nBytes);
    int purge();
    int receive(unsigned char* rxBuffer, unsigned long nBytes);
    int getQueLen(unsigned long * nBytes);
    ~ftdi();
};
