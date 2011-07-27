#include <stdio.h>
#include <stdlib.h>

int main(){
	char *s;
	
	printf("Hello %-*s end\n", 10,"123");
	printf("Hello %*s end\n", 10,"123");
	exit(0);

}
