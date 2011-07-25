#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

//#define S_IRWXU 00700
//#define S_IRUSR 00400
//#define S_IWUSR 00200
//#define S_IXUSR 00100
//
//#define S_IRWXG 00070
//#define S_IRGRP 00040
//#define S_IWGRP 00020
//#define S_IXGRP 00010
//
//#define S_IRWXO 00007
//#define S_IROTH 00004
//#define S_IWOTH 00002
//#define S_IXOTH 00001


int main(){

	char c;
	int in, out;
	
	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, 0666);
//	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while(read(in, &c, 1) == 1)
		write(out, &c, 1);

	exit(0);
}
