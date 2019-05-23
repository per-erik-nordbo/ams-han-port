
#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

#if defined(__linux__) || defined(__FreeBSD__) || defined(__CYGWIN__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/file.h>
#include <errno.h>

#endif
 
int open_serial(char *, int, const char *);
int serial_read(int, unsigned char *, int);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
