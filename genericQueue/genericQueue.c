#include "genericQueue.h"
#include <stdio.h>
#include <stdlib.h>
#define MAGIC 67895

struct Queue
{
	size_t m_size;
	size_t m_head; /* Index of head in m_vec. */
	size_t m_tail; /* Index of tail in m_vec. */
	size_t m_nItems;
	int m_magic;
	void* m_que[1];
};

Queue* Queue_Create(size_t _maxSize)
{
	Queue* newQ = NULL;
	if(_maxSize == 0)
	{
		return NULL;
	}
	if(!(newQ = (Queue*)malloc(sizeof(Queue) + (_maxSize - 1) * sizeof(void*))))
	{
		free(newQ);
		return NULL;
	}
	/*newQ->m_que = (void**)(newQ + 1);*/
	newQ->m_magic = MAGIC;
	newQ->m_size = _maxSize;
	newQ->m_nItems = 0;
	newQ->m_head = 0;
	newQ->m_tail = 0;
	return newQ;
}

void Queue_Destroy(Queue** _queue, void (*_elementDestroy)(void* _item))
{
	size_t i;
	size_t head;
	if (_queue == NULL || *_queue == NULL || (*_queue)->m_magic != MAGIC)
	{
		return;
	}
	if ((*_queue)->m_que)
	{
		if (_elementDestroy != NULL)
		{
			head = (*_queue)->m_head;
			for(i = 0; i < (*_queue)->m_nItems; i++)
			{
				_elementDestroy((*_queue)->m_que[head]);
				head = (head + 1) % (*_queue)->m_size;
			}
		}
	}
	(*_queue)->m_magic = 0;
	free(*_queue);
	*_queue = NULL;
}

Queue_Result Queue_Enqueue(Queue* _queue, void* _item)
{
    if(NULL == _queue || NULL == _item)
    {
        return QUEUE_UNINITIALIZED_ERROR;
    }
    
    if(_queue->m_nItems == _queue->m_size)
    {
        return QUEUE_OVERFLOW;   
    }
    
    _queue->m_que[_queue->m_tail] = _item;
    _queue->m_tail= (_queue->m_tail + 1) % _queue->m_size;
    ++_queue->m_nItems;
    return QUEUE_SUCCESS;
}

Queue_Result Queue_Dequeue(Queue* _queue, void** _pValue)
{
    if(NULL == _queue || NULL == _pValue)
    {
        return QUEUE_UNINITIALIZED_ERROR;
    }
    if(_queue->m_nItems == 0)
    {
        return QUEUE_UNDERFLOW; 
    }    
    
    *_pValue = (void*)_queue->m_que[_queue->m_head];
    _queue->m_head = (_queue->m_head +1 ) % _queue->m_size;
    --_queue->m_nItems;
    return QUEUE_SUCCESS; 
}

int Queue_IsEmpty(const Queue* _queue)
{
    return (NULL == _queue || _queue->m_nItems == 0);
}



