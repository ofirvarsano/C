#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define SIZE 50000

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int arr[], int left, int right)
{
	int i,j;
	int pivot = arr[right];
	i = (left - 1);
	for(j = left; j <= right-1; ++j)
	{
		if(arr[j] < pivot)
		{
			++i;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[right]);
	return i + 1;
}

void QuickSortRec(int arr[], int start, int end)
{
	int pivot;
	if(start < end)
	{
		pivot = Partition(arr, start, end);
		if(pivot > start)
		{
			QuickSortRec(arr, start, pivot - 1);
		}
		if(pivot < end)
		{
			QuickSortRec(arr, pivot + 1, end);
		}
	}
}

int BinarySearch(int arr[],int left, int right, int num)
{
	int middle;
	if(right >= left)
	{
		middle = left + (right - left) /2;
		if(arr[middle] == num)
		{
			return middle;
		}
		if(arr[middle] > num)
		{
			return BinarySearch(arr, left, middle - 1, num);
		}
		return BinarySearch(arr, middle + 1, right, num);
	}
	return -1;
}

int isExist(int arr[],int size,int num)
{
	int i;
	for(i = 0; i < size;++i)
	{
		if(arr[i] == num)
		{
			return 1;
		}
	}
	return 0;
}

int isExistEff(int arr[],int size,int num)
{
	int temp,i = 0;
	if(arr[size-1] == num)
	{
		return 1;
	}
	temp = arr[size-1];
	arr[size-1] = num;
	while(arr[i] != num)
	{
		++i;
	}
	arr[size-1] = temp;
	if(i == size-1)
	{
		return 0;
	}
	return 1;
}

int JumpSearch(int arr[], int size, int num)
{
	int i,j,m;
	i = 0;
	m = sqrt(size);
	
	while(arr[m] <= num && m < size)
	{
		i = m;
		m += sqrt(size);
		if(m > size - 1)
		{
			m = size;
		}
	}
	for(j = i; j < m; ++j)
	{
		if(arr[j] == num)
		{
			return j;
		}
	}

	return -1;
}

void PrintArray(int* _arr,int _size)
{
	int i;
	for(i=0;i<_size-1;i++)
	{
		printf("%d, ",_arr[i]);
	}
	printf("%d\n",_arr[i]);
}

int main()
{
	int i,x;
	int seed = SIZE;
	clock_t t;
	double cpuTime;
	int* a = NULL;
	
	a = (int*)malloc(SIZE*sizeof(int));
	
	srand(time(NULL));
	for(i=0; i<SIZE; i++)
	{
		x = rand() % seed;
		a[i] = x;
	}
	
	t = clock();
	for(i = 0; i < SIZE; ++i)
	{
		isExistEff(a,SIZE,i);
	}
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("isExistEff func took: %f seconds\n",cpuTime);
	
	t = clock();
	for(i = 0; i < SIZE; ++i)
	{
		isExist(a,SIZE,i);
	}
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("isExist func took: %f seconds\n",cpuTime);
	
	QuickSortRec(a,0,SIZE-1);
	t = clock();
	for(i = 0; i < SIZE; ++i)
	{
		BinarySearch(a,0,SIZE - 1,i);
	}
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("BinarySearch func took: %f seconds\n",cpuTime);
	
	t = clock();
	for(i = 0; i < SIZE; ++i)
	{
		JumpSearch(a,SIZE,i);
	}
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("JumpSearch func took: %f seconds\n",cpuTime);
	
	return 0;
}
