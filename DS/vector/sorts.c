#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"
#include "stack.h"
#define SIZE 50000
#define DIGIT_SIZE 10

static int Partition(Vector* _vec, int left, int right)
{
	int pVal,lVal,rVal;
	int pivot = left;
	VectorGet(_vec,pivot,&pVal);
	
	while(right > left)
	{
		VectorGet(_vec,left,&lVal);
		while(lVal <= pVal && left <= right)
		{
			++left;
			VectorGet(_vec,left,&lVal);
		}
		VectorGet(_vec,right,&rVal);
		while(rVal > pVal)
		{
			--right;
			VectorGet(_vec,right,&rVal);
		}
		if(left < right)
		{
			VectorSet(_vec,left,rVal);
			VectorSet(_vec,right,lVal);
		}
	}
	VectorGet(_vec,right,&rVal);
	VectorSet(_vec,right,pVal);
	VectorSet(_vec,pivot,rVal);
	return right;
}

void QuickSortRec(Vector* _vec, int start, int end)
{
	int pivot;
	if(_vec == NULL)
	{
		return;
	}
	if(start < end)
	{
		pivot = Partition(_vec, start, end);
		if(pivot > start)
		{
			QuickSortRec(_vec, start, pivot - 1);
		}
		if(pivot < end)
		{
			QuickSortRec(_vec, pivot + 1, end);
		}
	}
}

void QuickSortIterative(Vector* _vec)
{
	int num,pivot,left,right;
	Stack* stack = NULL;
	VectorItemsNum(_vec,&num);
	left = 0;
	right = num - 1;
	stack = StackCreate(num,10);
	if(stack == NULL)
	{
		return;
	}
	StackPush(stack,left);
	StackPush(stack,right);
	while(!StackIsEmpty(stack))
	{
		StackPop(stack,&right);
		StackPop(stack,&left);
		pivot = Partition(_vec, left, right);
		if(pivot - 1 > left)
		{
			StackPush(stack,left);
			StackPush(stack,pivot - 1);
		}
		if(pivot + 1 < right)
		{
			StackPush(stack,pivot + 1);
			StackPush(stack,right);
		}
	}
	StackDestroy(stack);
}

static int FindMin(Vector* _vec,int _from,int _to)
{
	int i,minVal,temp;
	int minIndex = _from;

	VectorGet(_vec,minIndex,&minVal);
	for(i = _from + 1; i < _to; ++i)
	 {
	 	VectorGet(_vec,i,&temp);
	 	if(temp < minVal)
	 	{
	 		minVal = temp;
	 		minIndex = i;
	 	}
	 }
	return minIndex;
}

void SelectionSort(Vector* _vec)
{
	int i,n,temp,first;
	int minIndex = 0;
	if(_vec == NULL)
	{
		return;
	}
	VectorItemsNum(_vec,&n);
	
	for(i = 0; i < n; ++i)
	{
		minIndex = FindMin(_vec,i,n);
		
		VectorGet(_vec,minIndex,&temp);
		VectorGet(_vec,i,&first);
		
		VectorSet(_vec,minIndex,first);
		VectorSet(_vec,i,temp);
	}
}

/* O(n^2) */
void InsertionSort(Vector* _vec)
{
	int i,j,n,value,jVal;
	if(_vec == NULL)
	{
		return;
	}
	VectorItemsNum(_vec,&n);
	
	for(i = 1; i < n; ++i)
	{
		VectorGet(_vec,i,&value);
		
		j = i -1;
		VectorGet(_vec,j,&jVal);
		while(j >= 0 && jVal > value)
		{
			VectorSet(_vec,j + 1,jVal);
			--j;
			VectorGet(_vec,j,&jVal);
		}
		VectorSet(_vec,j + 1,value);
	}
}

void ShellSort(Vector* _vec)
{
	int i,j,n,inc,temp,temp2;
	if(_vec == NULL)
	{
		return;
	}
	VectorItemsNum(_vec,&n);
	inc = n / 2;
	while(inc > 0)
	{
		for(i = inc; i < n; ++i)
		{
			VectorGet(_vec,i,&temp);
			j = i;
			VectorGet(_vec,j - inc,&temp2);
			while(j >= inc && temp2 > temp)
			{
				VectorSet(_vec,j,temp2);
				j -= inc;
				VectorGet(_vec,j - inc,&temp2);
			}
			VectorSet(_vec,j,temp);
		}
		inc = inc / 2;
	}
}

static int BubbleLine(Vector* _vec, int _start, int _end, int _jump)
{
	int i;
	int swapped = 0;
	int temp,temp2;
	
	for(i = _start; i != _end; i += _jump)
	{
		VectorGet(_vec,i,&temp);
 		VectorGet(_vec,i+1,&temp2);
		if(temp > temp2)
		{
			VectorSet(_vec,i,temp2);
			VectorSet(_vec,i+1,temp);
			swapped = 1;
		}
	}
	return swapped;
}

/* O(n^2) */
void ShakerSort(Vector* _vec)
{
	int end;
	int n;
	int swapped = 1;
	int start = 0;
	if(_vec == NULL)
	{
		return;
	}
	VectorItemsNum(_vec,&n);
	end = n-1;
	
	while(swapped)
	{
		swapped = BubbleLine(_vec, start, end, 1);
		if(!swapped)
		{
			break;
		}
		--end;
		swapped = BubbleLine(_vec, end - 1, start -1, -1);

		++start;
	}
}

/* O(n^2) */
void BubbleSort(Vector* _vec)
{ 
   register int i;
   int n;
   int swapped;
   if(_vec == NULL)
   {
		return;
   }
   VectorItemsNum(_vec,&n);
   for (i = 0; i < n-1; ++i)
   { 
     swapped = 0;
     swapped = BubbleLine(_vec, 0, n-i-1, 1);

     if (!swapped) 
        break; 
   } 
}

/* O(nlogn) */
void Merge(Vector* _vec,int left,int middle, int right)
{
	int i,j,k,temp;
	int leftSize = middle - left + 1;
	int rightSize = right - middle;
	int* L = NULL;
	int* R = NULL;
	
	if(_vec == NULL)
	{
		return;
	}
   
	L = (int*)calloc(leftSize,sizeof(int));
	R = (int*)calloc(rightSize,sizeof(int));
	if(L == NULL || R == NULL)
	{
		return;
	}
	for(i = 0; i < leftSize; ++i)
	{
		VectorGet(_vec,left + i,&temp);
		L[i] = temp;
	}
	for(i = 0; i < rightSize; ++i)
	{
		VectorGet(_vec,middle + i + 1,&temp);
		R[i] = temp;
	}
	k = left;
	i = 0;
	j = 0;
	while(i < leftSize && j < rightSize)
	{
		if(L[i] <= R[j])
		{
			VectorSet(_vec,k,L[i]);
			++i;
		}
		else
		{
			VectorSet(_vec,k,R[j]);
			++j;
		}
		++k;
	}
	while(i < leftSize)
	{
		VectorSet(_vec,k,L[i]);
		++i;
		++k;
	}
	while(j < rightSize)
	{
		VectorSet(_vec,k,R[j]);
		++j;
		++k;
	}
	free(L);
	free(R);
}

void MergeSortRec(Vector* _vec,int left, int right)
{
	int middle;
	if(_vec == NULL)
	{
		return;
	}
	if(left < right)
	{
		middle = left + (right - left) / 2;
		
		MergeSortRec(_vec,left,middle);
		MergeSortRec(_vec,middle + 1,right);
		
		Merge(_vec,left,middle,right);
	}
}

static void CountArray(int arr[], int _size, Vector* _vec)
{
	int i,temp;
	for(i = 0; i < _size; ++i)
	{
		VectorGet(_vec,i,&temp);
		arr[temp]++;
	}
}

static void Acumulated(int arr[], int _size)
{
	int i;
	for(i = 1; i < _size; ++i)
	{
		arr[i] += arr[i-1];
	}
}

static void BuildSortArray(int arr[],int arr2[], int _size,Vector* _vec)
{
	int i,temp;
	for(i = _size - 1; i >= 0; --i)
	{
		VectorGet(_vec,i,&temp);
		
		arr2[arr[temp]-1] = temp;
		arr[temp]--;
	}
}

static void CopyArrayToVector(int arr[], int _size,Vector* _vec)
{
	int i;
	for(i = 0; i < _size; ++i)
	{
		VectorSet(_vec,i,arr[i]);
	}
}

void CountingSort(Vector* _vec, int _maxVal)
{
	int n,cSize;
	int* b = NULL;
	int* c = NULL;
	if(_vec == NULL)
	{
		return;
	}
	cSize = _maxVal + 1;
	VectorItemsNum(_vec,&n);
	
	c = (int*)calloc(cSize,sizeof(int));
	b = (int*)calloc(n,sizeof(int));
	
	if(c == NULL || b == NULL)
	{
		return;
	}
	
	CountArray(c,n,_vec);
	Acumulated(c,cSize);
	BuildSortArray(c,b,n,_vec);
	CopyArrayToVector(b,n,_vec);

	free(b);
	free(c);
}

/* TODO Generic count with function pointer to a funcion
that calculata temp / place % 10
*/
void CountingSortDigit(Vector* _vec,int place)
{
	int n,i,temp;
	int* b = NULL;
	int* count = NULL;
	if(_vec == NULL)
	{
		return;
	}
	VectorItemsNum(_vec,&n);
	b = (int*)calloc(n,sizeof(int));
	count = (int*)calloc(DIGIT_SIZE,sizeof(int));
	if(b == NULL || count == NULL)
	{
		return;
	}
	for(i = 0; i < n; ++i)
	{
		VectorGet(_vec,i,&temp);
	
		count[(temp / place) % 10]++;
	}
	Acumulated(count,DIGIT_SIZE);
	for(i = n-1; i >= 0; --i)
	{
		VectorGet(_vec,i,&temp);
		b[count[(temp / place) % 10] - 1] = temp;
		count[(temp / place) % 10]--;
	}
	CopyArrayToVector(b,n,_vec);
	
	free(b);
	free(count);
}

void RadixSort(Vector* _vec,int _nDigits)
{
	int place,i;
	place = 1;
	if(_vec == NULL)
	{
		return;
	}
	for(i = 0; i < _nDigits; ++i)
	{
		CountingSortDigit(_vec,place);
		place *= 10;
	}
}

int main()
{
	int i,x;
	int seed = SIZE;
	clock_t t;
	double cpuTime;
	Vector* vecPtr = NULL;
	Vector* vecPtr1 = NULL;
	Vector* vecPtr2 = NULL;
	Vector* vecPtr3 = NULL;
	Vector* vecPtr4 = NULL;
	Vector* vecPtr5 = NULL;
	Vector* vecPtr6 = NULL;
	Vector* vecPtr7 = NULL;
	Vector* vecPtr9 = NULL;
	Vector* vecPtr10 = NULL;
	vecPtr = VectorCreate(100,100);
	vecPtr1 = VectorCreate(100,100);
	vecPtr2 = VectorCreate(100,100);
	vecPtr3 = VectorCreate(100,100);
	vecPtr4 = VectorCreate(100,100);
	vecPtr5 = VectorCreate(100,100);
	vecPtr6 = VectorCreate(100,100);
	vecPtr7 = VectorCreate(100,100);
	vecPtr9 = VectorCreate(100,100);
	vecPtr10 = VectorCreate(100,100);
	if(vecPtr == NULL || vecPtr2 == NULL || vecPtr3 == NULL || vecPtr4 == NULL || vecPtr5 == NULL || vecPtr6 == NULL || vecPtr7 == NULL || vecPtr9 == NULL || vecPtr10 == NULL || vecPtr1 == NULL)
	{
		return(0);
	}
	srand(time(NULL));
	for(i=0; i<SIZE; i++)
	{
		x = rand() % seed;
		VectorAddEnd(vecPtr,x);
		VectorAddEnd(vecPtr1,x);
		VectorAddEnd(vecPtr2,x);
		VectorAddEnd(vecPtr3,x);
		VectorAddEnd(vecPtr4,x);
		VectorAddEnd(vecPtr5,x);
		VectorAddEnd(vecPtr6,x);
		VectorAddEnd(vecPtr7,x);
		VectorAddEnd(vecPtr9,x);
		VectorAddEnd(vecPtr10,x);
	}
	t = clock();
	CountingSort(vecPtr3,SIZE);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("CountingSort func took:\t\t%f seconds\n",cpuTime);
	
	t = clock();
	RadixSort(vecPtr,4);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("RadixSort func took:\t\t%f seconds\n",cpuTime);

	t = clock();
	QuickSortRec(vecPtr5,0,SIZE - 1);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("QuickSortRec func took:\t\t%f seconds\n",cpuTime);
	
	t = clock();
	QuickSortIterative(vecPtr6);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("QuickSortIterative func took:\t%f seconds\n",cpuTime);
	
	t = clock();
	MergeSortRec(vecPtr2,0,SIZE - 1);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("MergeSort func took:\t\t%f seconds\n",cpuTime);
	
	t = clock();
	ShellSort(vecPtr7);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("ShellSort func took:\t\t%f seconds\n",cpuTime);
	
	t = clock();
	InsertionSort(vecPtr4);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("InsertionSort func took:\t%f seconds\n",cpuTime);
	
	t = clock();
	SelectionSort(vecPtr1);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("SelectionSort func took:\t%f seconds\n",cpuTime);
	
	t = clock();
	ShakerSort(vecPtr10);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("ShakerSort func took:\t\t%f seconds\n",cpuTime);
	
	t = clock();
	BubbleSort(vecPtr9);
	t = clock() - t;
	cpuTime = ((double)t)/CLOCKS_PER_SEC;
	printf("BubbleSort func took:\t\t%f seconds\n",cpuTime);
	
	VectorDestroy(vecPtr);
	VectorDestroy(vecPtr2);
	VectorDestroy(vecPtr3);
	VectorDestroy(vecPtr4);
	VectorDestroy(vecPtr5);
	VectorDestroy(vecPtr6);
	VectorDestroy(vecPtr7);
	VectorDestroy(vecPtr9);
	VectorDestroy(vecPtr10);
	
	return 0;
}


