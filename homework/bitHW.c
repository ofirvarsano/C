#include <stdio.h>
#include <stdlib.h>
#define BYTE_SIZE 8

unsigned int TableBitFlip[8][255];

int isPowerOfTwoLUT(unsigned int x)
{
	unsigned int powersOfTwo[32] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,
    65536,131072,262144,524288,1048576,2097152,4194304,8388608,
    16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648};

	int exponent = 0;

	while (powersOfTwo[exponent] < x && exponent < 31)
	{
		exponent++;
	}
	return (x == powersOfTwo[exponent]);
}

int isPowerOfTwo(int x)
{
	return x && (!(x&(x-1)));
}

int addBitwise(int x, int y)
{
	int c;
	while(x != 0)
	{
		c = y & x;
		y = y ^ x;
		x = c << 1;
	}
	return y;
}

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

void invert(unsigned char x, int start, int end)
{
	int i;
	unsigned char y = x;
	for(i=start; i < end; i++)
	{
		y ^= (1 << i);
	}
	printf("x = ");
	printBits(x,BYTE_SIZE);
	printf("\ny = ");
	printBits(y,BYTE_SIZE);
	printf("\n");
}

unsigned char rotateRight(int n,unsigned char rotation)
{
	int i;
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

int findSingle(int arr[], int size)
{
	int i;
	int result = arr[0];
	for(i = 1; i < size; ++i)
	{
		result = result ^ arr[i];
	}
	return result;
}

int multiply3point5(int x)
{
	return (x << 1) + x + (x >> 1);
}

void buildLUT()
{
	int i,j;
	for(j = 0; j < 8; ++j)
	{
		for( i = 0; i < 256; ++i)
		{
			TableBitFlip[j][i] ^= (1 << j);
		}
	}
}

void initializeLUT()
{
	int i,j;
	for(j = 0; j < 8; ++j)
	{
		for( i = 0; i < 256; ++i)
		{
			TableBitFlip[j][i] = i;
		}
	}
}

int main()
{
	printf("%d\n",isPowerOfTwoLUT(1));
	printf("%d\n",isPowerOfTwoLUT(2));
	printf("%d\n",isPowerOfTwoLUT(8));
	printf("%d\n",isPowerOfTwoLUT(15));
	
	printf("%d\n",addBitwise(15,3));

	printBits(2,8);
	printf("\n");
	printBits(5,8);
	printf("\n");

	invert(128,0,8);
	invert(128,3,5);

	printf("%d\n",multiply3point5(5));

	initializeLUT();
	buildLUT();
	
	printf("\n");
	printBits(TableBitFlip[0][0],8);
	printf("\n");
	printBits(TableBitFlip[1][1],8);
	printf("\n");
	printBits(TableBitFlip[1][2],8);
	printf("\n");
	printBits(TableBitFlip[2][2],8);
	printf("\n");
	return 0;
}
