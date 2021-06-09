#include "vector.h"
#include "heap.h"
#include <stdio.h>

void test1()
{
	int max;
	Vector* vecPtr = NULL;
	Heap* heap = NULL;
	vecPtr = VectorCreate(3,2);
	if(vecPtr == NULL)
	{
		exit(0);
	}
	VectorAddEnd(vecPtr,7);
	VectorAddEnd(vecPtr,6);
	VectorAddEnd(vecPtr,3);
	VectorAddEnd(vecPtr,20);
	VectorAddEnd(vecPtr,5);
	VectorAddEnd(vecPtr,5);
	VectorPrint(vecPtr);
	heap = HeapBuild(vecPtr);
	printf("\n\n");
	HeapPrint(heap);
	printf("\n\n");
	HeapInsert(heap,40);
	HeapPrint(heap);
	printf("\n\n");
	HeapInsert(heap,35);
	HeapPrint(heap);
	printf("\n\n");
	HeapInsert(heap,35);
	HeapPrint(heap);
	printf("\n\n");
	HeapExtractMax(heap,&max);
	printf("%d\n",max);
	HeapPrint(heap);
	printf("\n\n");
	HeapExtractMax(heap,&max);
	printf("%d\n",max);
	HeapPrint(heap);
	HeapDestroy(heap);
	VectorDestroy(vecPtr);
}

int main()
{

	test1();
	
	return 0;
}
