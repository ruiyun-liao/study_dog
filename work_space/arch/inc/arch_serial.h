#ifndef __ARCH_SERIAL_H__
#define __ARCH_SERIAL_H__

#include "total_define.h"

#ifdef __cplusplus
extern "C" {
#endif

int arch_serial_open(char *device, int baud);
int arch_serial_close(int fd);
int arch_serial_put(int fd, unsigned char c);
int arch_serial_puts(int fd, char *s);
int arch_serial_data_avail(int fd);
int arch_serial_getchar(int fd);
int arch_serial_flush(int fd);

#ifdef __cplusplus
}
#endif

#endif