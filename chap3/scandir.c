#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void printdir(DIR *, int);
void printdt(const char *dname);
int isdir(const char *dname);

int main(int argc, char *argv[]){
	
	DIR *directory;
	char *dirname;
        struct stat statbuff;

        dirname = argv[1];

        if(!isdir(dirname)){
                printdt(dirname);
                exit(0);
        }

	if(argc != 3){
		printf("Usage: scandir [directory name] [depth]\n");	
		exit(-1);
	}

        int depth;
        depth = atoi(argv[2]);

        if((directory = opendir(dirname)) == NULL){
                fprintf(stderr,"Open directory failed: %s\n", dirname);
                exit(1);
        }

	printdir(directory, depth);

	exit(0);
	
}

void printdir(DIR *directory, int depth){

	if(depth < 0)
		return;

	struct dirent *dt;

	while(dt = readdir(directory)){
		if (strcmp(".", dt->d_name) == 0 || strcmp("..", dt->d_name) == 0)
			continue;
		if(isdir(dt->d_name)){
			printdir(opendir(dt->d_name), depth-1);
		}
		printdt(dt->d_name);
	}


}

int isdir(const char *dname){
        struct stat statbuff;
        lstat(dname, &statbuff);
        return S_ISDIR(statbuff.st_mode);
}

void printdt(const char *dname){

	struct stat statbuff;
	unsigned long modes;
	lstat(dname, &statbuff);
	modes = statbuff.st_mode;
	printf("Mode: %lo\n", modes);
	printf("%lo,%lo,%lo,%lo\n", (modes & S_IFMT), (modes & S_IRWXU), (modes & S_IRWXG), (modes & S_IRWXO));

        switch(modes & S_IFMT) {
           case S_IFBLK:  printf("b");        break;
           case S_IFCHR:  printf("c");        break;
           case S_IFDIR:  printf("d");        break;
           case S_IFIFO:  printf("f");        break;
           case S_IFLNK:  printf("l");        break;
           case S_IFREG:  printf("-");        break;
           case S_IFSOCK: printf("s");        break;
           default:       printf("?");        break;
        }


//----------------------------------------------------------
	switch(modes & S_IRWXU) {
	  case S_IRWXU:  printf("rwx");       break;
	  case S_IRUSR:  printf("r--");       break;
	  case S_IWUSR:  printf("-w-");       break;
	  case S_IXUSR:  printf("--x");       break;
	  default:	 printf("---");	      break;

	}

//----------------------------------------------------------
	switch(modes & S_IRWXG) {
	  case S_IRWXG:  printf("rwx");       break;
	  case S_IRGRP:  printf("r--");       break;
	  case S_IWGRP:  printf("-w-");       break;
	  case S_IXGRP:  printf("--x");       break;
	  default:	 printf("---");	      break;

	}

//----------------------------------------------------------
	switch(modes & S_IRWXO) {
	  case S_IRWXO:  printf("rwx");       break;
	  case S_IROTH:  printf("r--");       break;
	  case S_IWOTH:  printf("-w-");       break;
	  case S_IXOTH:  printf("--x");       break;
	  default:	 printf("---");	      break;

	}

//----------------------------------------------------------
	printf("\t");
	printf("%ld\t", (long) statbuff.st_size);
	printf("%ld %ld\t", (long)statbuff.st_uid, (long)statbuff.st_gid);
	printf("%-10s\n", dname);
}
