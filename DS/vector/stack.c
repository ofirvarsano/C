#include "vector.h"
#include "stack.h"
#include <stdio.h>
#define MAGIC 45678

struct Stack
{
	Vector* vector;
	int m_magic;
};

Stack* StackCreate(size_t _size, size_t _blockSize)
{
	Stack* newStack = NULL;
	if(_blockSize <1)
	{
		return NULL;
	}
	newStack = (Stack*)malloc(sizeof(Stack));
	if(NULL == newStack)
	{
		return NULL;
	}
	newStack->vector = VectorCreate(_size, _blockSize);
	if(NULL == newStack->vector)
	{
		free(newStack);
		return NULL;
	}
	newStack->m_magic = MAGIC;
	return newStack;
}

void StackDestroy(Stack* _stack)
{
	if(_stack && _stack->m_magic == MAGIC)
	{
		VectorDestroy(_stack->vector);
		_stack->m_magic = 0;
		free(_stack);
	}
}

ADTErr StackPush(Stack* _stack, int _item)
{
	if(_stack)
	{
		return VectorAddEnd(_stack->vector, _item);
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	if(_stack && _item)
	{
		return VectorDeleteEnd(_stack->vector, _item);
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr StackTop(Stack* _stack, int* _item)
{
	int numOfItems;
	if(_stack && _item)
	{
		VectorItemsNum(_stack->vector, &numOfItems);
		if(numOfItems == 0)
		{
			return ERR_UNDERFLOW;
		}
		return VectorGet(_stack->vector, numOfItems-1, _item);
	}
	return ERR_NOT_INITIALIZED;
}

int StackIsEmpty(Stack* _stack)
{
	int numOfItems;
	if(_stack)
	{
		VectorItemsNum(_stack->vector, &numOfItems);
		if(numOfItems == 0)
		{
			return 1;
		}
	}
	return 0;
}

void StackPrint(Stack* _stack)
{
	if(_stack)
	{
		VectorPrint(_stack->vector);
	}
}


