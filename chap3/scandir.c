#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int condepth;

void printdir(char *dirname, int depth);
void printdt(const char *dname, int depth);
int isdir(const char *dname);

int main(int argc, char *argv[])
{
	
	char *dirname;
        struct stat statbuff;
	
        if((argc != 3) && (argc != 2)){
                printf("Usage: scandir [directory name] [depth],  Or scandir [file name]\n");
                exit(EINVAL);
        }

        dirname = argv[1];

	if(argc == 2){
       		if(!isdir(dirname)){
        	        printdt(dirname, 0);
                	exit(0);
        	}
		if(fopen(dirname,"r") == NULL){
			fprintf(stderr,"Open directory failed: %s, the reason is: ", dirname);
			perror("");
		}
		else
			printf("%s is a directory, please input the [depth]\n", dirname);
		exit(EINVAL);
	}
        int depth;
        condepth = depth = atoi(argv[2]);

	printdir(dirname, depth);

	exit(0);
	
}

void printdir(char *dirname, int depth)
{

	if(depth < 0)
		return;
	DIR *directory;
        if((directory = opendir(dirname)) == NULL){
                fprintf(stderr,"Open directory failed: %s, the reason is: ", dirname);
		perror("");
		return;
        }
	chdir(dirname);

	struct dirent *dt;

	while(dt = readdir(directory)){
		if (strcmp(".", dt->d_name) == 0 || strcmp("..", dt->d_name) == 0)
			continue;
		printdt(dt->d_name, depth);
		if(isdir(dt->d_name)){
			printdir(dt->d_name, depth-1);
		}
	}
	chdir("..");
	closedir(directory);

}

int isdir(const char *dname)
{
        struct stat statbuff;
        if(lstat(dname, &statbuff)){
		printf("Fail to stat %s\n", dname);
		return 2;
	}
        return S_ISDIR(statbuff.st_mode);
}

void printdt(const char *dname, int depth)
{

	struct stat statbuff;
	unsigned long modes;
	lstat(dname, &statbuff);
	modes = statbuff.st_mode;

	int i = condepth - depth;
        for(; i>0; i--)
                printf("\t");

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
	if(modes & S_IRUSR)
		printf("r");
	else	
		printf("-");
	if(modes & S_IWUSR)
		printf("w");
	else	
		printf("-");
	if(modes & S_IXUSR)
		printf("x");
	else	
		printf("-");

//----------------------------------------------------------
	if(modes & S_IRGRP)
		printf("r");
	else	
		printf("-");
	if(modes & S_IWGRP)
		printf("w");
	else	
		printf("-");
	if(modes & S_IXGRP)
		printf("x");
	else	
		printf("-");

//----------------------------------------------------------
	if(modes & S_IROTH)
		printf("r");
	else	
		printf("-");
	if(modes & S_IWOTH)
		printf("w");
	else	
		printf("-");
	if(modes & S_IXOTH)
		printf("x");
	else	
		printf("-");

//----------------------------------------------------------
	printf("\t");
	printf("%ld\t", (long) statbuff.st_size);
	printf("%ld %ld\t", (long)statbuff.st_uid, (long)statbuff.st_gid);
	printf("%-10s\n", dname);
}
