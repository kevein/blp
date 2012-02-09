#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int i;
  time_t the_time, time2;
  
  time_t *buff;
  buff = malloc(sizeof(time_t));
  /*
    You can also use this:
    time_t buff;
    time2 = time(&buff);
    void time(&buff);
   */
  
  for(i = 1; i <= 10; i++){
    the_time = time((time_t *)0); //return time to a time_t var
    time2 = time(buff); //put the time to a time_t address "buff", while return it
    printf("The time is %ld\n", the_time);
    printf("The time is %ld\n", time2);
    printf("The time is %ld\n", *buff);
    sleep(2);
  }
  exit(0);
}
