#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t n;
	n = fork();
	n = fork();
	n = fork();
	/*
	int d[] = {1,5,7};
	int *p = &d[1];
	printf("%d", *p--);
	printf("%d", *p);
	printf("%d%d%d", d[0],d[1],d[2]);
	*/
	return 0;	
}
