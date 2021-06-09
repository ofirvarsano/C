#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 30000
#define SWAP(x,y) \
{ \
int temp; \
temp = x; \
x = y; \
y = temp; \
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

void Swap(int* _xp, int* _yp) 
{ 
    int temp = *_xp; 
    *_xp = *_yp; 
    *_yp = temp; 
}

void MacroBubbleSort(int _arr[], int _n)
{ 
   register int i, j; 
   int swapped; 
   for (i = 0; i < _n-1; i++)
   { 
     swapped = 0; 
     for (j = 0; j < _n-i-1; j++) 
     { 
        if (_arr[j] > _arr[j+1]) 
        {
        	SWAP(_arr[i],_arr[j+1])
           swapped = 1; 
        } 
     }
     if (!swapped) 
        break; 
   } 
}

void BubbleSort(int _arr[], int _n) 
{ 
   register int i, j; 
   int swapped; 
   for (i = 0; i < _n-1; i++)
   { 
     swapped = 0; 
     for (j = 0; j < _n-i-1; j++) 
     { 
        if (_arr[j] > _arr[j+1]) 
        { 
           Swap(&_arr[j], &_arr[j+1]); 
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
	int seed;
	int arr[SIZE];
	int arr2[SIZE];
	clock_t t;
	double cpuTime;
	double macroCpuTime;
	
	srand(time(NULL));
	printf("Pick seed\n");
	scanf("%d",&seed);
	for(i=0; i<SIZE; i++)
	{
		arr[i]= rand() % seed;
		arr2[i] = arr[i];
	}

	/*PrintIntArray(arr,sizeof(arr)/sizeof(arr[0]));*/
	t = clock();
	BubbleSort(arr,SIZE);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("BubbleSort func took: %f seconds\n",cpuTime);
	t = clock();
	MacroBubbleSort(arr2,SIZE);
	t = clock() - t;
	macroCpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("BubbleSort func took: %f seconds\n",macroCpuTime);
	printf("difference of: %f seconds\n",cpuTime - macroCpuTime);
	
	/*PrintIntArray(arr,sizeof(arr)/sizeof(arr2[0]));*/
	
	return 0;
}


