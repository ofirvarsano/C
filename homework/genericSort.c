#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*func)(const void*, const void*);

int compareInt(const void* a, const void*b)
{
	int* c = (int*)a;
	int* d = (int*)b;
	return *c - *d;
}

int compareString(const void* a, const void*b)
{
	const char *c = (char*)a;
	const char *d = (char*)b;
	return strcmp(c,d);
}

int GenericSort(void* _elements, size_t _elementsCount, size_t _elementSize, func _f)
{
	int i,j,k;
	void* ptr = _elements;
	void* temp[256];
	
	if(_elementsCount < 2 || _elementSize == 0)
	{
		return 1;
	}
	for(i = _elementsCount - 1; i >=0; --i)
	{
		for(j = 1; j <= i; ++j)
		{
			k = _f((void*)(ptr + _elementSize * (j-1)), (void*)(ptr + _elementSize * j));
			if(k > 0)
			{
				memcpy(temp, ptr+_elementSize * (j-1), _elementSize);
				memcpy(ptr+_elementSize * (j-1), ptr+_elementSize * j, _elementSize);
				memcpy(ptr+_elementSize * j, temp, _elementSize);
			}
		}
	}
	return 1;
}

int main()
{
	int i;
	int arr[] = {1,7,4,9,15,5,5,6};
	func f;
	size_t numOfElems, elemSize, numOfStrElems, elemStrSize;
	
	char str[6][20] = {"abc","cbb","z","abx","aaa","caa"};
	
	numOfStrElems = sizeof(str)/sizeof(str[0]);
	elemStrSize = sizeof(str[0]);
	
	numOfElems = sizeof(arr)/sizeof(arr[0]);
	elemSize = sizeof(arr[0]);
	
	for(i = 0; i < numOfStrElems; ++i)
	{
		printf("%s, ",str[i]);
	}
	printf("\n");
	
	for(i = 0; i < numOfElems; ++i)
	{
		printf("%d, ",arr[i]);
	}
	printf("\n");
	
 	
	f = compareInt;
	GenericSort(arr, numOfElems, elemSize, f);
	for(i = 0; i < numOfElems; ++i)
	{
		printf("%d, ",arr[i]);
	}
	printf("\n");
	
	f = compareString;
	GenericSort(str, numOfStrElems, elemStrSize, f);
	for(i = 0; i < numOfStrElems; ++i)
	{
		printf("%s, ",str[i]);
	}
	
	return 0;
}
