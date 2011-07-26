#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	
	char *filename;
	struct stat statbuff;
	mode_t modes;
	int filedes;

	if(argc != 2){
		printf("Usage: filestat [file name]\n");
		exit(1);
	}
	
	filename = argv[1];
	filedes = open(filename, O_RDONLY);
	if (filedes < 0){
		perror("open failed");
		exit(1);
	}
	fstat(filedes, &statbuff);
	modes = statbuff.st_mode;

	printf("File type:	");

	switch (statbuff.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
	}
	printf("Mode:	%lo (octal)\n", (unsigned long)modes);
	printf("Link count:	%d\n", (long)statbuff.st_nlink);
	printf("Ownership:	UID=%ld, GID=%ld\n", (long)statbuff.st_uid, (long)statbuff.st_gid);
	printf("Preferred I/O block size:	%ld bytes\n", (long)statbuff.st_blksize);
	printf("File size:	%ld\n", (long)statbuff.st_size);
	printf("Blocks allocated:	%ld\n", (long)statbuff.st_blocks);
	printf("Last status change:       %s", ctime(&statbuff.st_ctime));
        printf("Last file access:         %s", ctime(&statbuff.st_atime));
        printf("Last file modification:   %s", ctime(&statbuff.st_mtime));

	close(filedes);	
	exit(0);	
		
}
