#include <stdio.h>
#include <time.h>

int main (int argc,
	  char *argv[])
{
  time_t ret;
  struct tm info;
  char buffer[80];
  
  info.tm_year = 2017 - 1900;
  info.tm_mon = 10 - 1;
  info.tm_mday = 9;
  info.tm_hour = 22;
  info.tm_min = 59;
  info.tm_sec = 03;
  info.tm_isdst = -1;
  
  ret = mktime(&info);
  if( ret == -1 ) {
    printf("Error: unable to make time using mktime\n");
  } else {
    strftime(buffer, sizeof(buffer), "%c", &info );
    printf("%s\n", buffer);
    printf("%s\n", ctime(&ret));
  }
  
  return(0);
}
