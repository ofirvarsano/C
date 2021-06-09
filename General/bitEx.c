#include <stdio.h>
#include <stdlib.h>
#define BYTE_SIZE 8
void printBits(int number,int n)
{
	int bit;
	if(number || n)
	{
		printBits(number >>1,n-1);
		bit = (number&1) ? 1 : 0;
		printf("%d",bit);
	}
}

unsigned char rotateRight(int n,unsigned char rotation)
{
	int i;
	unsigned char e;
	printBits(rotation,BYTE_SIZE);
	n = n % BYTE_SIZE;
	printf("\n");
	for(i=0;i<n;i++)
	{
		rotation >>= 1;
		if(rotation & 1)
		{
			rotation |= (1 << (BYTE_SIZE-1));
		}
	}
	printBits(rotation,BYTE_SIZE);
	printf("\n");
	return rotation;
}

void invert(unsigned char x)
{
	int i;
	unsigned char y = x;
	for(i=0;i<sizeof(unsigned char)*BYTE_SIZE;i++)
	{
		y ^= (1 << i);
	}
	printf("x = ");
	printBits(x,BYTE_SIZE);
	printf("\ny = ");
	printBits(y,BYTE_SIZE);
	printf("\n");
}  
int TestBit(unsigned int _num)
{
	int i;
	int count = 0;
	unsigned int e;
	for(i=0;i<sizeof(unsigned int)*BYTE_SIZE;i++)
	{
		e = _num & (1 << i);
		if(e)
		{
			count++;
		}
	}
	return count;
}
int main()
{
	/*unsigned int x = 42949251;
	printf("%d\n",TestBit(x));
	printBits(1,8);
	printf(" ");
	printBits(3,8);
	printf(" ");
	printBits(8,8);
	printf("\n");*/
	invert(8);
	printf("\n");
	invert(0);
	printf("\n");
	invert(149);
	printf("\n");
	rotateRight(3,140);
	return 0;
}
