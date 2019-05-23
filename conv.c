#include <stdio.h>

int main()
{
    unsigned int d;
    
    while (scanf("%02x", &d) == 1) {
      printf("%c", (unsigned char) d);
    }
    
    return 0;
}
