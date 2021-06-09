#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#define MAGIC 56789

struct Queue
{
	int* m_que;
	size_t m_size;
	size_t m_head; /* Index of head in m_vec. */
	size_t m_tail; /* Index of tail in m_vec. */
	size_t m_nItems;
	int m_magic;
};

Queue* QueueCreate(size_t _size)
{
	Queue* newQ = NULL;
	if(_size == 0)
	{
		return NULL;
	}
	newQ = (Queue*)malloc(sizeof(Queue) + _size * sizeof(int));
	if(NULL == newQ)
	{
		return NULL;
	}
	newQ->m_que = (int*)(newQ + 1);
	newQ->m_magic = MAGIC;
	newQ->m_size = _size;
	newQ->m_nItems = 0;
	newQ->m_head = 0;
	newQ->m_tail = 0;
	return newQ;
}

void QueueDestroy(Queue* _queue)
{
	if(_queue && _queue->m_magic == MAGIC)
	{
		_queue->m_magic = 0;
		free(_queue);
	}
}

ADTErr QueueInsertCheckError(Queue* _queue)
{
	if(_queue && _queue->m_magic == MAGIC)
	{
		if(_queue->m_nItems == _queue->m_size)
		{
			return ERR_OVERFLOW;
		}
		return ERR_OK;
	}
	return ERR_NOT_INITIALIZED;
}

ADTErr QueueInsert(Queue* _queue,int _item)
{
	ADTErr err;
	err = QueueInsertCheckError(_queue);
	if(err != ERR_OK)
	{
		return err;
	}
	_queue->m_que[_queue->m_tail] = _item;
	_queue->m_tail = (_queue->m_tail+1)%_queue->m_size;
	_queue->m_nItems++;
	return ERR_OK;
}

ADTErr QueueDleteCheckError(Queue* _queue,int *_item)
{
	if(_queue && _queue->m_magic == MAGIC && _item)
	{
		if(_queue->m_nItems == 0)
		{
			return ERR_UNDERFLOW;
		}
		return ERR_OK;
	}
	return ERR_NOT_INITIALIZED;

}
ADTErr QueueRemove(Queue* _queue,int *_item)
{
	ADTErr err;
	err = QueueDleteCheckError(_queue,_item);
	if(err != ERR_OK)
	{
		return err;
	}
	*_item = _queue->m_que[_queue->m_head];
	_queue->m_head = (_queue->m_head+1)%_queue->m_size;
	_queue->m_nItems--;
	return ERR_OK;
}

int QueueIsEmpty(Queue* _queue)
{
	if(_queue && _queue->m_magic == MAGIC)
	{
		int num = _queue->m_nItems;
		if(num != 0)
		{
			return 0;
		}
	}
	return 1;
}

void QueuePrint(Queue* _queue)
{
	int i;
	size_t head;
	if(_queue && _queue->m_magic == MAGIC)
	{
		head = _queue->m_head;
		for(i=0;i<_queue->m_nItems;i++)
		{
			printf("%d ",_queue->m_que[head]);
			head = (head+1)%_queue->m_size;
		}
		printf("\n");
	}
}


