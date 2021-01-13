//#include <stdio.h>
#include <wiringSerial.h>
#include "arch_serial.h"

int arch_serial_open(char *device, int baud)
{
    return serialOpen (device, baud);
}

int arch_serial_close(int fd)
{
    serialClose (fd);
    return 0;
}

int arch_serial_put(int fd, unsigned char c)
{
    serialPutchar (fd, c);
    return 0;
}

int arch_serial_puts(int fd, char *s)
{
    serialPuts (fd, s);
    return 0;
}

int arch_serial_data_avail(int fd)
{
    return serialDataAvail(fd);
}

int arch_serial_getchar(int fd)
{
    return serialGetchar(fd);
}

int arch_serial_flush(int fd)
{
    serialFlush(fd);
    return 0;
}
