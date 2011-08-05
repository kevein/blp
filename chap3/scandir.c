#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	DIR *directory;
	struct dirent *dt;
	struct stat statbuf;

	if(argc != 2)
		printf("Usage: scandir [directory name]");	
	if((directory = opendir(argv[1])) == NULL){
		perror("open directory:");
		return 1;
	}
	
	while(dt = readdir(directory)){
		printf("inode number: %10ld\t  Name: %10s\n", (long) dt->d_ino, dt->d_name);	
	}	

	

	exit(0);
	
}
