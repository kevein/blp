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
  int fd, fd2;
  ssize_t rdlink;
  char tmpstr[50];
  filename2 = malloc(sizeof(char)*50);
  
  char template[] = "/tmp/Kevein_XXXXXX";
  
  filename = tmpnam(tmpname);

  printf("Temporay file name is: %s\n", filename);
  tmpfp = tmpfile();

  if(tmpfp)
    printf("Opened a temporary file OK\n");
  else
    perror("tmpfile");
  
  fd = fileno(tmpfp);
  
  sprintf(tmpstr, "/proc/%d/fd/%d", getpid(),fd);
  
  rdlink= readlink(tmpstr, filename2, 50);
  printf("Created by tmpfile(): %s\n", filename2);

  fd2 = mkstemp(template);
  bzero(tmpstr, 50);
  bzero(filename2, 50);
  sprintf(tmpstr, "/proc/%d/fd/%d", getpid(),fd2);
  printf("%s\n", tmpstr);
  rdlink= readlink(tmpstr, filename2, 50);
  printf("Created by mkstemp(): %s\n", filename2);
  
  /* sleep(60);  */

  exit(0);
}
