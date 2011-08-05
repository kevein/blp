#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int filedes;
	char *buff;
	
	filedes = open("unlinkf", O_CREAT|O_RDWR, 0644);
	unlink("unlinkf");
	
	buff = "Test";
	write(filedes, buff,5);
	read(filedes, buff, 5);
	printf("%s\n", buff);
	
	sleep(21);
	
//	unlink("unlinkf");  //if unlink() function goes to here, you will see the file
	
	exit(0);
}
