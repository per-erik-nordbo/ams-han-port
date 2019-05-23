#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Enable both ECB and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DECB=1
#define CBC 1
#define ECB 1

#include "aes.h"

/**************************************************************************************************************************************
 * FUNCTION: phex()
 *************************************************************************************************************************************/
void phex(uint8_t* str)
{
    unsigned char i;
    for(i = 0; i < 16; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}

/**************************************************************************************************************************************
 * FUNCTION: main()
 *************************************************************************************************************************************/
int main()
{
	 
  uint8_t key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  uint8_t crypted[] = {0xd3, 0x79, 0x5d, 0x95, 0xea, 0x76, 0x1b, 0x5a, 0x2b, 0x18, 0x80, 0x76, 0x80, 0x20, 0xe4, 0x99,
		      0xd3, 0xfd, 0x39, 0xa4, 0xc3, 0x59, 0x8c, 0x7f, 0x94, 0x29, 0x40, 0xde, 0xa5, 0xda, 0x9c, 0x22};

  uint8_t decrypted[16];

  AES128_ECB_decrypt(crypted, key, decrypted);
  phex(decrypted);

  AES128_ECB_decrypt(crypted+16, key, decrypted);
  phex(decrypted);
    
  return 0;
}

/* end of file */
