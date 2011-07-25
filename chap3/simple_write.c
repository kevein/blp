#include <unistd.h>
#include <stdlib.h>

//size_t write(int filedes, const void *buf, size_t nbytes);

int main(){
	if((write(1, "Here is some data\n", 18)) != 18)
		write(2, "A write error has occurred on file descriptor 1\n", 46)
	exit(2);
}
