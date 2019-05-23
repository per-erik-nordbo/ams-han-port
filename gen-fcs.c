#include <stdio.h>

/*
 * Generate a FCS-16 table.
 *
 * Drew D. Perkins at Carnegie Mellon University.
 *
 * Code liberally borrowed from Mohsen Banan and D. Hugh Redelmeier.
 */

/*
 * The FCS-16 generator polynomial: x**0 + x**5 + x**12 + x**16.
 */

#define P 0x8408

/*
 * NOTE The hex to "least significant bit" binary always causes
 * confusion, but it is used in all HDLC documents. Example: 03H
 * translates to 1100 0000B. The above defined polynomial value
 * (0x8408) is required by the algorithm to produce the results
 * corresponding to the given generator polynomial
 * (x**0 + x**5 + x**12 + x**16)
 */

int main()
{
  register unsigned int b, v;
  register int i;
  printf("typedef unsigned short u16;\n");
  printf("static u16 fcstab[256] = {");
  for (b = 0; ; ) {
    if (b % 8 == 0)
      printf("\n");
    v = b;
    for (i = 8; i--; )
      v = v & 1 ? (v >> 1) ^ P : v >> 1;
    printf("\t0x%04x", v & 0xFFFF);
    if (++b == 256)
      break;
    printf(",");
  }
  printf("\n};\n");
  return 0;
}

/* end of file */
