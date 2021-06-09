#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_i;
int g_j = 0;
int g_k = 5;

static int s_i;
static int s_j = 0;
static int s_k = 5;

int main()
{
	int l;
	static int s_l;
	static int s_m = 5;
	char* str = "abc";
	printf("%p %p %p\n",(void*)&g_i,(void*)&g_j,(void*)&g_k);
	printf("%p %p %p\n",(void*)&s_i,(void*)&s_j,(void*)&s_k);
	printf("%p %p %p\n",(void*)&l,(void*)&s_l,(void*)&s_m);
	printf("%p\n",(void*)str);
	return 0;
}
