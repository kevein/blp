#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


int main()
{
	int fd, newfd, fdwithcloexec;

	fd = open("file.in", O_RDONLY);
	printf("The original fd is %d\n", fd);	

	newfd = fcntl(fd, F_DUPFD, fd+1);	
	printf("The duplicated fd is %d\n", newfd);
	
	int flag;
	flag = fcntl(newfd, F_GETFD);
	printf("The FD_CLOEXEC of newfd is %d\n", flag);
	
	if (flag != 1)
	{
		fcntl(newfd, F_SETFD, 1);
		printf("Succeed to set the FD_CLOEXEC for newfd\n");
	}

        flag = fcntl(newfd, F_GETFD);
        printf("After fcntl, the FD_CLOEXEC of newfd is %d\n", flag);

	fdwithcloexec = open("file.in", O_RDONLY|O_CLOEXEC);
	flag = fcntl(fdwithcloexec, F_GETFD);
        printf("The FD_CLOEXEC of fdwithcloexec is %d\n", flag);

	pid_t pid;
	pid = getpid();
	printf("The pid of this process is %d\n", (int)pid);

	sleep(20);
	
	exit(0);
	
}
