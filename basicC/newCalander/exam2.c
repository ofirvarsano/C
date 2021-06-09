#include <stdio.h>
int main() 
{
	int x[] = {1, 2, 3, 4, 5};
	int i;
	int* ptr = x;
	*(ptr+3) = 10;
	/*
	*ptr + 3 = 10;
	*ptr[ 3 ] = 10;
	
	*(ptr + 3) = 10;
	
	(*ptr)[ 3 ] = 10;
	*(ptr[ 3 ]) = 10;
	*/
	for( i = 0; i < 5; i++ ) 
	{
		printf("%d ", x[i]);
	}
	return 0;
}
