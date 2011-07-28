#include <stdio.h>
#include <stdlib.h>

int main(){
	char *s;
	int num;
	char string[1024];
	
	printf("Hello %-*s end\n", 10,"123");
	printf("Hello %*s end\n", 10,"123");
	num = -1;
	scanf("Hello %d", &num);
	printf("The scan result is: %d\n", num);
	scanf("%[^,]",string);
	printf("The string is: %s\n", string);
	exit(0);

}
