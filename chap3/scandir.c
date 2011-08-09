#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void printdir(const char *, int);
void printdt(struct dirent *dt);
int isdir(struct dirent *dt);

int main(int argc, char *argv[]){
	int depth = 0;

	if(argc != 3){
		printf("Usage: scandir [directory name] [depth]\n");	
		exit(-1);
	}
	
	depth = atoi(argv[2]);	

	printdir(argv[1], depth);

	exit(0);
	
}

void printdir(const char *dirname, int depth){

        DIR *directory;
	struct dirent *dt;
	int i;
//	printf("In printdir: directory name %s\n", dirname);

        if((directory = opendir(dirname)) == NULL){
                fprintf(stderr,"Open directory failed: %s\n", dirname);
                exit(1);
        }
	chdir(dirname);
	while(dt = readdir(directory)){
		if (strcmp(".", dt->d_name) == 0 || strcmp("..", dt->d_name) == 0)
			return;
		printdt(dt);
	}


}

int isdir(struct dirent *dt){
        struct stat statbuff;
        lstat(dt->d_name, &statbuff);
        return S_ISDIR(statbuff.st_mode);
}

void printdt(struct dirent *dt){

	struct stat statbuff;
	mode_t modes;
	lstat(dt->d_name, &statbuff);
	
	modes = statbuff.st_mode;
	printf("%lo\t", (unsigned long) modes);
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
	printf("%-10s\n", dt->d_name);
}
