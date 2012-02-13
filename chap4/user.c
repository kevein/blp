#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>

int main()
{
  uid_t uid;
  gid_t gid;

  struct passwd *pw;
  uid = getuid();
  gid = getgid();

  printf("User is %s\n", getlogin());
  printf("User IDs: uid=%d, gid=%d\n", uid, gid);
  
  pw = getpwuid(uid);
  /* pw = getpwnam(getlogin()); */
  printf("UID passwd entry:\n name=%-8s, uid=%-3d, gid=%-3d, home=%-15s, shell=%-10s, Full Name=%-10s\n", pw->pw_name, pw->pw_uid,\
	 pw->pw_gid, pw->pw_dir, pw->pw_shell, pw->pw_gecos);
  
  pw = getpwnam("root");
  printf("ROOT passwd entry:\n name=%-8s, uid=%-3d, gid=%-3d, home=%-15s, shell=%-10s, Full Name=%-10s\n", pw->pw_name, pw->pw_uid, \
	 pw->pw_gid, pw->pw_dir, pw->pw_shell, pw->pw_gecos);

  while((pw = getpwent()) != NULL){
    if(pw->pw_uid != (uid_t)38)
      printf("It's %s\n", pw->pw_name);
    else{
      printf("Hi, this is ntp user!\n");
      break;
    }
  }
  endpwent();

  exit(0);
}
