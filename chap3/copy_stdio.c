#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1024

int main(){
//	int c;
//	FILE *in, *out;

//	in = fopen("file.in", "r");
//	out = fopen("file.out", "a");

//	while((c = fgetc(in)) != EOF)
//		fputc(c, out);
//------------------------------------------------------------
	char s[BUFFSIZE];
	FILE *in, *out;
	int errnum;
	
	in = fopen("file.in", "r");
	out = fopen("file.out", "a");
	
	while((fgets(s, BUFFSIZE, in)) != NULL)
		fprintf(out, "%s", s);
	
	errnum = ferror(in);
	if(errnum)
		printf("Something wrong in stream file.in, %d\n", errnum);
	if(feof(in))
		printf("We're at end of file.in\n");

	exit(0);
}
