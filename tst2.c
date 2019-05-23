#include <stdio.h>

int main()
{
  unsigned char byte2 = 0xa2;
  unsigned char byte3 = 0x3c;

  unsigned char type = byte2 & 0xa0;
  if (type == 0xa0) {
    printf("correct type!\n");
  }
  else {
    printf("wrong message type!\n");
  }

  unsigned int len = ((byte2 & 0x07) << 8) + byte3;
  printf("len: %1d\n", len);
  
  return 0; 
}
