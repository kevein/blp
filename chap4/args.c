#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	int arg, opt=1;
	if(argc < 2){
		printf("Please give more options and arguments!\n");
		exit(-213);
	}
	for (arg = 1; arg < argc; arg++) {
		if(argv[arg][0] == '-')
			printf("option: %s\t", argv[arg]+1);
		else {
			printf("argument %d: %s\t", opt, argv[arg]);
			opt++;
		}
	}
	printf("\n");
	exit(0);
}
