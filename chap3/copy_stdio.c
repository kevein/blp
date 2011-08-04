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
	
	in = fopen("file.in", "r");
	out = fopen("file.out", "a");
	
	while((fgets(s, BUFFSIZE, in)) != NULL)
		fprintf(out, "%s", s);

	exit(0);
}
