#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define LENTH_NAME 20

int main()
{
  char tmpname[LENTH_NAME];
  char *filename, *filename2;
  FILE *tmpfp;
  int fd;
  ssize_t rdlink;
  char tmpstr[50], buff[15];
  filename2 = malloc(sizeof(char)*30);
  
  filename = tmpnam(tmpname);

  printf("Temporay file name is: %s\n", filename);
  tmpfp = tmpfile();

  if(tmpfp)
    printf("Opened a temporary file OK\n");
  else
    perror("tmpfile");
  
  fd = fileno(tmpfp);
  
  strcpy(tmpstr, "/proc/");
  sprintf(buff, "%d/fd/%d", getpid(),fd);
  strcat(tmpstr,buff);
  
  rdlink= readlink(tmpstr, filename2, 30);
  printf("Created by tmpfile(): %s\n", filename2);
  
  sleep(60);

  exit(0);
}
