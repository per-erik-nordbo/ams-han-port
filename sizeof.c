#include <stdio.h>
#include <stdlib.h>

int main()
{
  typedef struct {
    long a;
    long b;
    long c[10];
  } X;
  X *x;

  x = (X *) malloc(sizeof(X));

  x->a = 1;
  x->b = 2;
  
  printf("%1d %1d %1d\n", (int) sizeof(X), (int) sizeof(x), (int) sizeof(*x));

  return 0;
}
  
