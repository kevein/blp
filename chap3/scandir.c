#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int printdir(const char *, int);
int isdir = 0;

int main(int argc, char *argv[]){
	int depth = 0;

	if(argc != 3){
		printf("Usage: scandir [directory name] [depth]\n");	
		return -1;
	}
	
	depth = atoi(argv[2]);	

	printdir(argv[1], depth);

	exit(0);
	
}

int printdir(const char *dirname, int depth){

        DIR *directory;
	struct dirent *dt;
	int i;
        extern int isdir;

        if((directory = opendir(dirname)) == NULL){
                fprintf(stderr,"open directory : %s\n", dirname);
                return 1;
        }
	for(i = 0; i <= depth; i++){
		while(dt = readdir(directory)){
			if(isdir && (depth -i > 0)){
				printdt(dt);
				printdir(dt->d_name, depth-1);
			}
			printdt(dt);
		}
	}


}

int printdt(struct dirent *dt){
	int i;
	struct stat statbuff;
	extern int isdir;
	lstat(dt->d_name, &statbuff);

	if(S_ISDIR(statbuff.st_mode)){
		printf("d");	
		isdir = 1;
	}
	if(S_ISREG(statbuff.st_mode))
		printf("-");
	if(S_ISCHR(statbuff.st_mode))
		printf("c");
	if(S_ISBLK(statbuff.st_mode))
		printf("b");
	if(S_ISFIFO(statbuff.st_mode))
		printf("f");
	if(S_ISLNK(statbuff.st_mode))
		printf("l");
	if(S_ISSOCK(statbuff.st_mode))
		printf("s");
//----------------------------------------------------------
	if(S_IRUSR & statbuff.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWUSR & statbuff.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXUSR & statbuff.st_mode)
		printf("x");
	else
		printf("-");

//----------------------------------------------------------
	if(S_IRGRP & statbuff.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWGRP & statbuff.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXGRP & statbuff.st_mode)
		printf("x");
	else
		printf("-");

//----------------------------------------------------------
	if(S_IROTH & statbuff.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWOTH & statbuff.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXOTH & statbuff.st_mode)
		printf("x");
	else
		printf("-");

//----------------------------------------------------------
	printf("\t");
	printf("%10s\n", dt->d_name);
}
