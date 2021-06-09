#include <stdlib.h> /* size_t */
/* TODO error.h */
#ifndef _QUEUE_H_
#define _QUEUE_H_
typedef enum
{
ERR_OK =0,
ERR_NOT_INITIALIZED,
ERR_UNDERFLOW,
ERR_OVERFLOW
} ADTErr;

typedef struct Queue Queue;

/* Description:
function creates a new queue
input- receives size for the initial queue (size>0)
output- returns a pointer to the new queue
errors- no errors - return NULL if not succeed
complixity- O(1) */
Queue* QueueCreate(size_t _size);


/* Description:
destroys queue and free all its memory
input- pointer to a queue
output- non
errors- non
complixity- O(1) */
void QueueDestroy(Queue* _queue);


/* Description:
insert a value to the queue
input- pointer to queue, int item to insert
output- ADTErr error
errors- ERR_NOT_INITIALIZED if queue is NULL
ERR_OVERFLOW if theres no room. (queue is full)
ERR_OK if succeed
complixity- O(1) */
ADTErr QueueInsert(Queue* _queue,int _item);


/* Description:
remove a value from the queue to item-int pointer
input- pointer to queue, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if queue or item is NULL
ERR_UNDERFLOW if queue is empty
ERR_OK if succeed
complixity- O(1) */
ADTErr QueueRemove(Queue* _queue,int *_item);


/* Description:
returns 1 if queue is empty or NULL, 0 if not
input- pointer to queue
output- int
errors- non
complixity- O(1) */
int QueueIsEmpty(Queue* _queue);


/* Description:
prints queue
input- pointer to queue
output- non
errors- non
complixity- O(n) */
void QueuePrint(Queue* _queue);
#endif
