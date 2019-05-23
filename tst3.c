#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"

int main()
{
  int count;
  unsigned char buf[1000];
  char device[100] = "/dev/ttyUSB0";
  char mode[]={'8','N','1',0}; /* bits-in-byte, parity, stop-bits, end-string */
  int bdrate=2400; /* 2400 baud */

  int fd = open(device, O_RDONLY);

  open_serial(device, bdrate, mode);
  
  while (1) {
    if ((count = read(fd, buf, 10)>0)) {
      int i;
      for (i=0; i<count; i++) {
	if (buf[i] == 0x7e) {
	  printf("\n");
	}
	printf("%1x ", buf[i]);
	fflush(stdout);
      }
    }
  }

  return 0;
}

/************** end of file ******************/
