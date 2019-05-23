#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
 
void print_current_time_with_ms (void);
 
int main()
{
  print_current_time_with_ms();
 
  return 0;
}
 
void print_current_time_with_ms (void)
{
  long ms; // Milliseconds
  time_t s;  // Seconds
  struct timespec spec;
  char buf[100], buf2[100];
 
  clock_gettime(CLOCK_REALTIME, &spec); /* OR: CLOCK_MONOTIC */
 
  s  = spec.tv_sec;
  ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
 
  printf("64 bit Current time: %"PRIdMAX".%03ld seconds since the Epoch\n", (intmax_t)s, ms);
  strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&s));
  ms = 1;
  sprintf(buf2, ".%03ld", ms);
  strcat(buf, buf2);
  printf("%s\n", buf);
 
  return;
}
