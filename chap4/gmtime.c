#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  struct tm *tm_ptr;
  time_t raw_time;
  
  (void) time(&raw_time);
  tm_ptr = gmtime(&raw_time);

  printf("Raw time is %ld\n", raw_time);
  printf("\n");  

  printf("gmtime() provides:\n");
  printf("date: %04d/%02d/%02d\n", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday);
  printf("time: %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
  printf("\n");

  tm_ptr = localtime(&raw_time);
  printf("localtime() provides:\n");  
  printf("date: %04d/%02d/%02d\n", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday);
  printf("time: %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
  printf("\n");
  
  char * ctime_str;
  ctime_str = ctime(&raw_time);
  printf("ctime() provides:\n");
  printf("%s\n", ctime_str);
  
  char * asctime_str;
  asctime_str = asctime(tm_ptr);
  printf("asctime() provides:\n");
  printf("%s\n", asctime_str);

  exit(0);
}
