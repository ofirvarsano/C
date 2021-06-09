#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 50
#define SWAP(x,y) \
{ \
int temp; \
temp = x; \
x = y; \
y = temp; \
}

typedef int(*funcPointer)(int,int);

int IncreaseSort(int a, int b)
{
	return a > b;
}

int DecreseSort(int a, int b)
{
	return b > a;
}

int LastDigitSort(int a, int b)
{
	return a % 10 > b % 10;
}

int SumOftDigitsSort(int a, int b)
{
	int countA = 0;
	int countB = 0;
	while(a > 0)
	{
		countA += a % 10;
		a /= 10;
	}
	while(b > 0)
	{
		countB += b % 10;
		b /= 10;
	}
	return countA > countB;
}

void PrintIntArray(int* _arr,int _size)
{
	int i;
	for(i=0;i<_size-1;i++)
	{
		printf("%d, ",_arr[i]);
	}
	printf("%d\n",_arr[i]);
}

void BubbleSort(funcPointer f, int _arr[], int _n)
{ 
   register int i, j;
   int swapped;
   if(!f)
   {
		return;
	}
   for (i = 0; i < _n-1; i++)
   {
     swapped = 0; 
     for (j = 0; j < _n-i-1; j++) 
     { 
        if ((*f)(_arr[j],_arr[j+1])) 
        {
			SWAP(_arr[j],_arr[j+1])
			swapped = 1; 
        } 
     }
     if (!swapped)
        break; 
   } 
}

int main()
{
	int i;
	int arr[SIZE];
	funcPointer p;
	
	srand(time(NULL));
	for(i=0; i<SIZE; i++)
	{
		arr[i]= rand() % 100;
	}

	PrintIntArray(arr,sizeof(arr)/sizeof(arr[0]));
	printf("\n\n");
	
	p = SumOftDigitsSort;
	BubbleSort(p,arr,SIZE);
	printf("After BubbleSort\n");
	
	PrintIntArray(arr,sizeof(arr)/sizeof(arr[0]));
	
	return 0;
}
