#include "genericHeap.h"
#include "../genericVector/genericVector.h"
#include <stdlib.h>
#define PARENT(i) (i-1)/2
#define LEFT(i) (2*(i) + 1)
#define RIGHT(i) (2*(i) + 2)
#define MAGIC 8956

struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	LessThanComparator m_compareFunc;
	int m_magic;
};

static void Heapify(Heap* _heap, int _index);
static int FindLargestValueIndex(Heap* _heap, int _index);
static void swap(Vector* _vec, int _i, int _j, void* _iVal, void* _jVal);
static void BubbleUp(Heap* _heap,int i);

Heap* Heap_Build(Vector* _vector, LessThanComparator _pfLess)
{
	int i;
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if (heap == NULL || _vector == NULL || _pfLess == NULL)
	{
		return NULL;
	}
	heap->m_vec = _vector;
	heap->m_heapSize = Vector_Size(heap->m_vec);
	heap->m_compareFunc = _pfLess;
	heap->m_magic = MAGIC;
	
	i = PARENT(heap->m_heapSize -1);
	for (;i >= 0; --i)
	{
		Heapify(heap,i);
	}
	return heap;
}

Vector* Heap_Destroy(Heap** _heap)
{
	Vector* vecToReturn = NULL;
	if (_heap && *_heap && (*_heap)->m_magic == MAGIC)
	{
		if((*_heap)->m_vec)
		{
			vecToReturn = (*_heap)->m_vec;
		}
		(*_heap)->m_magic = 0;
		free(*_heap);
		(*_heap) = NULL;
	}
	return vecToReturn;
}

static void Heapify(Heap* _heap, int _index)
{
	int largest;
	void* iVal,*largestVal;
	
	if ( _heap == NULL || _index >= _heap->m_heapSize)
	{
		return;
	}
	largest = FindLargestValueIndex(_heap,_index);
	
	if (largest != _index)
	{
		Vector_Get(_heap->m_vec, _index,&iVal);
		Vector_Get(_heap->m_vec,largest,&largestVal);
		swap(_heap->m_vec,_index,largest,iVal,largestVal);
		Heapify(_heap,largest);
	}
}

static void swap(Vector* _vec, int _i, int _j, void* _iVal, void* _jVal)
{
	Vector_Set(_vec,_i,_jVal);
	Vector_Set(_vec,_j,_iVal);
}

static int FindLargestValueIndex(Heap* _heap, int _index)
{
	int l,r,largest;
	void* leftVal,*rightVal,*largestVal;
	
	l = LEFT(_index);
	r = RIGHT(_index);
	largest = _index;
	Vector_Get(_heap->m_vec, l, &leftVal);
	Vector_Get(_heap->m_vec, r, &rightVal);
	Vector_Get(_heap->m_vec, _index, &largestVal);
	
	if (l < _heap->m_heapSize && _heap->m_compareFunc(leftVal,largestVal))
	{
		largest = l;
		largestVal = leftVal;
	}
	if (r < _heap->m_heapSize && _heap->m_compareFunc(rightVal,largestVal))
	{
		largest = r;
	}
	return largest;
}

Heap_ResultCode Heap_Insert(Heap* _heap, void* _element)
{
	Heap_ResultCode heapErr;
	Vector_Result vecErr;
	int i;
	if (_heap == NULL || _heap->m_vec == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	vecErr = Vector_Append(_heap->m_vec,_element);
	switch (vecErr)
	{
		case VECTOR_SUCCESS:
				++_heap->m_heapSize;
				i = _heap->m_heapSize - 1;
				BubbleUp(_heap,i);
				return HEAP_SUCCESS;
				break;
		case VECTOR_ALLOCATION_ERROR:
				heapErr = HEAP_REALLOCATION_FAILED;
				break;
		case VECTOR_UNITIALIZED_ERROR:
				heapErr = HEAP_NOT_INITIALIZED;
				break;
		default: heapErr = HEAP_REALLOCATION_FAILED; break;
	}
	return heapErr;
}

static void BubbleUp(Heap* _heap,int i)
{
	void* temp, *tempParent;
	Vector_Get(_heap->m_vec,PARENT(i),&tempParent);
	Vector_Get(_heap->m_vec,i,&temp);

	while(i != 0 && _heap->m_compareFunc(temp,tempParent))
	{
		swap(_heap->m_vec,i,PARENT(i),temp,tempParent);
		i = PARENT(i);
		
		Vector_Get(_heap->m_vec,PARENT(i),&tempParent);
		Vector_Get(_heap->m_vec,i,&temp);
	}
}

const void* Heap_Peek(const Heap* _heap)
{
	void* element;
	if(_heap == NULL || _heap->m_vec == NULL || _heap->m_heapSize == 0)
	{
		return NULL;
	}
	Vector_Get(_heap->m_vec,0,&element);
	return (const void*)element;
}

void* Heap_Extract(Heap* _heap)
{
	void* last, *element;
	if(_heap == NULL || _heap->m_vec == NULL || _heap->m_heapSize == 0)
	{
		return NULL;
	}
	if(_heap->m_heapSize == 1)
	{
		if(Vector_Remove(_heap->m_vec, &element) == VECTOR_SUCCESS)
		{
			--_heap->m_heapSize;
			return element;
		}
	}
	Vector_Get(_heap->m_vec,0,&element);
	Vector_Get(_heap->m_vec,_heap->m_heapSize - 1,&last);
	Vector_Set(_heap->m_vec,0,last);

	Vector_Remove(_heap->m_vec, &last);
	--_heap->m_heapSize;
	Heapify(_heap,0);
	return element;
}

size_t Heap_Size(const Heap* _heap)
{
	if(_heap == NULL || _heap->m_vec == NULL)
	{
		return 0;
	}
	return _heap->m_heapSize;
}



