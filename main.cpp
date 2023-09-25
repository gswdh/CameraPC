#include "mainwindow.h"

#include <QApplication>

#include "ftdi_axi_driver.h"
#include "ftdi_ft60x.h"

#include <stdint.h>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec()
*/

    // Open the port
    ftdi_ft60x port;
    if (!port.open(0))
    {
        printf("Could not open port\n");
        return -1;
    }

    // Reset target state machines
    ftdi_axi_driver driver(&port);
    driver.send_drain(1000);
    port.sleep(10000);

    uint32_t addr = 0x0011b194;
    uint32_t value = 0;

    if (!driver.read32(addr, value))
    {
        printf("Read failed\n");
        return -1;
    }

    printf("0x%08x: 0x%08x (%d)\n", addr, value, value);

    port.close();
}
