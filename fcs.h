#ifndef FCS_INCLUDE_FILE
#define FCS_INCLUDE_FILE

#include <stdint.h>

#define PPPINITFCS16 0xffff /* Initial FCS value */
#define PPPGOODFCS16 0xf0b8 /* Good final FCS value */

typedef unsigned short u16;

int is_big_endian(void);

u16 pppfcs16(u16 fcs,
	     unsigned char *cp,
	     int len);
void tryfcs16(unsigned char *cp,
	      int len);

#endif
