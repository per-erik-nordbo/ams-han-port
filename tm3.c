#include <stdio.h>
#include <time.h>

int main ()
{
  int ret;
  struct tm info;
  char buffer[80];

  char tm_str[100] = "2017-06-07 22:25:30";

  int year, month, day;
  int hour, min, sec;

  printf("%s\n", tm_str);
  printf("count: %1d\n", sscanf(tm_str, "%4d-%2d-%2d %2d:%2d:%2d",
				&year, &month, &day,
				&hour, &min, &sec));
    
  info.tm_year = year - 1900;
  info.tm_mon = month - 1;
  info.tm_mday = day;
  info.tm_hour = hour;
  info.tm_min = min;
  info.tm_sec = sec;
  info.tm_isdst = -1;
  
  ret = mktime(&info);
  if( ret == -1 ) {
    printf("Error: unable to make time using mktime\n");
  } else {
    strftime(buffer, sizeof(buffer), "%c", &info );
    printf("%s\n", buffer);
  }
  
  return(0);
}
