#include <stdio.h>

int main(int argc, char *argv[])
{
  argc = argc;
  argv=argv;
  
  int c;
  int count=0;
  
  while ((c=getchar()) != EOF) {
    if (count>0) printf(" ");
    printf("%02x", c);
    count++;
  }
  
  return 0;
}
