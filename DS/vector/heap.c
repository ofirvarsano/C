#include "heap.h"

#define PARENT(i) (i-1)/2
#define LEFT(i) (2*(i) + 1)
#define RIGHT(i) (2*(i) + 2)
#define MAGIC 7895

struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	int m_magic;
};

/* Complexity: O(log n); */
static void Heapify(Heap* _heap, int i);
static void swap(Vector* _vec,int _i,int _j,int _iVal,int _jVal);
static void BubbleUp(Heap* _heap,int i);
static int FindLargestIndex(Heap* _heap, int _index);

Heap* HeapBuild(Vector* _vec)
{
	int i,itemsNum;
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if(heap == NULL || _vec == NULL)
	{
		return NULL;
	}
	heap->m_vec = _vec;
	VectorItemsNum(heap->m_vec,&itemsNum);
	heap->m_heapSize = (size_t)itemsNum;
	heap->m_magic = MAGIC;
	
	i = PARENT(heap->m_heapSize -1);
	for(;i >= 0; --i)
	{
		Heapify(heap,i);
	}
	return heap;
}

void HeapDestroy(Heap* _heap)
{
	if(_heap && _heap->m_magic == MAGIC)
	{
		_heap->m_magic = 0;
		free(_heap);
	}
}
static int FindLargestIndex(Heap* _heap, int _index)
{
	int l,r,largest,leftVal,rightVal,largestVal;
	
	l = LEFT(_index);
	r = RIGHT(_index);
	largest = _index;
	VectorGet(_heap->m_vec, l, &leftVal);
	VectorGet(_heap->m_vec, r, &rightVal);
	VectorGet(_heap->m_vec, _index, &largestVal);
	
	if(l < _heap->m_heapSize && leftVal > largestVal)
	{
		largest = l;
		largestVal = leftVal;
	}
	if(r < _heap->m_heapSize && rightVal > largestVal)
	{
		largest = r;
	}
	return largest;
}

static void Heapify(Heap* _heap, int _index)
{
	int largest,iVal,largestVal;
	
	if( _heap == NULL || _index >= _heap->m_heapSize)
	{
		return;
	}
	largest = FindLargestIndex(_heap,_index);
	
	if(largest != _index)
	{
		VectorGet(_heap->m_vec,_index,&iVal);
		VectorGet(_heap->m_vec,largest,&largestVal);
		swap(_heap->m_vec,_index,largest,iVal,largestVal);
		Heapify(_heap,largest);
	}
}

static void swap(Vector* _vec,int _i,int _j,int _iVal,int _jVal)
{
	VectorSet(_vec,_i,_jVal);
	VectorSet(_vec,_j,_iVal);
}

static void BubbleUp(Heap* _heap,int i)
{
	int temp,tempParent;
	VectorGet(_heap->m_vec,PARENT(i),&tempParent);
	VectorGet(_heap->m_vec,i,&temp);

	while(i != 0 && tempParent < temp)
	{
		swap(_heap->m_vec,i,PARENT(i),temp,tempParent);
		i = PARENT(i);
		
		VectorGet(_heap->m_vec,PARENT(i),&tempParent);
		VectorGet(_heap->m_vec,i,&temp);
	}
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	ADTErr err;
	int i;
	if(_heap == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorAddEnd(_heap->m_vec,_data);
	if(err == ERR_OK)
	{
		++_heap->m_heapSize;
		i = _heap->m_heapSize - 1;

		BubbleUp(_heap,i);
		return ERR_OK;
	}
	return err;
}

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	int last;
	if(_heap == NULL || _heap->m_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_heap->m_heapSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	if(_heap->m_heapSize == 1)
	{
		VectorDeleteEnd(_heap->m_vec,_data);
		--_heap->m_heapSize;
		return ERR_OK;
	}
	VectorGet(_heap->m_vec,0,_data);
	VectorGet(_heap->m_vec,_heap->m_heapSize - 1,&last);
	VectorSet(_heap->m_vec,0,last);

	VectorDeleteEnd(_heap->m_vec,&last);
	--_heap->m_heapSize;
	Heapify(_heap,0);
	return ERR_OK;
}

ADTErr HeapMax(Heap* _heap, int* _data)
{
	if(_heap == NULL || _heap->m_vec == NULL || _data == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_heap->m_heapSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	return VectorGet(_heap->m_vec,0,_data);
}

int HeapItemsNum(Heap* _heap)
{
	if(_heap == NULL || _heap->m_vec == NULL)
	{
		return 0;
	}
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	if(_heap)
	{
		VectorPrint(_heap->m_vec);
	}
}


