#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int opt;
	
	while((opt = getopt(argc, argv, ":if:lr")) != -1) {
		switch(opt) {
		case 'i':
		case 'r':
		case 'l':
			printf("option: %c\n", opt);
			break;
		case 'f':
			printf("filename: %s\n", optarg);
			break;
		case ':':
			printf("option -%c needs a value!\n", optopt);
			break;
		case '?':
			printf("unknown option: %c\n", optopt);
			break;
		}
	}	
	for(; optind < argc; optind++)	
		printf("argument: %s\n", argv[optind]);

	exit(0);
}
