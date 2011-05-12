#ifndef _SERIALCOMM_H_
#define _SERIALCOMM_H_

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define BAUDRATE B9600
#define DEVICE "/dev/ttyS1"
#define null   0x00
#define TIMEOUT -2
#define DEBUG 0
#define VERBOUSE 0
#define VERBOUSE_TIMEOUT 0

int serialport_init(const char* serialport, int baud);
int serialport_write(int fd, unsigned char* str);
int serialport_write_len(int fd, unsigned char* str, int len);
int serialport_read(int fd, unsigned char* str, int len, int timeout);
int serialport_close(int handler);
#endif // _SERIALCOMM_H_
