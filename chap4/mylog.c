#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *f;
  int logmask;
  f = fopen("not_here", "r");
  if(!f)
    syslog(LOG_ERR|LOG_USER, "oops: %m\n");
  openlog("logmask", LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_NOTICE, "Before logmask");
  logmask = setlogmask(LOG_UPTO(LOG_NOTICE));
  syslog(LOG_NOTICE, "After logmnask");
  syslog(LOG_INFO, "Should not appear");
  exit(0);
}
