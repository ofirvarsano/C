#include <stdio.h>
#include "../mu_test.h"
#include "genericQueue.h"


UNIT(Queue_Create_Null_args)
    ASSERT_THAT(Queue_Create(0) == NULL);
END_UNIT

UNIT(Queue_Create_creation_legal_values)
    Queue *queue = NULL;
    queue = Queue_Create(3);
    ASSERT_THAT(queue != NULL);
    Queue_Destroy(&queue, NULL);
END_UNIT

UNIT(Queue_Enqueue_Null_args)

    Queue *queue = NULL;
    int a = 5;
    
    queue = Queue_Create(10);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Enqueue(NULL, &a) == QUEUE_UNINITIALIZED_ERROR);
    ASSERT_THAT(Queue_Enqueue(queue, NULL) == QUEUE_UNINITIALIZED_ERROR);
    Queue_Destroy(&queue, NULL);  
END_UNIT

UNIT(Queue_Enqueue_to_built_queue)
    Queue *queue = NULL;
    int a=5, b=8, c=9, d=120;
    
    queue= Queue_Create(10);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Enqueue(queue, &a) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &b) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &c) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &d) == QUEUE_SUCCESS);
    Queue_Destroy(&queue, NULL);       
END_UNIT

UNIT(Queue_Enqueue_to_full_queue)
    Queue *queue = NULL;
    int a=5, b=8, c=9, d=120, e=150, f=23;
    
    queue= Queue_Create(6);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Enqueue(queue, &a) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &b) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &c) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &d) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &e) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &f) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &d) == QUEUE_OVERFLOW);
    Queue_Destroy(&queue, NULL); 
END_UNIT

UNIT(Queue_Dequeue_Null_args)
    Queue *queue = NULL;
    int *a;
    
    queue= Queue_Create(10);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Dequeue(NULL, (void**)&a) == QUEUE_UNINITIALIZED_ERROR);
    ASSERT_THAT(Queue_Dequeue(queue, NULL) == QUEUE_UNINITIALIZED_ERROR);
    Queue_Destroy(&queue, NULL);       
END_UNIT

UNIT(Queue_Dequeue_element)
    Queue *queue = NULL;
    int a=5, b=8, c=9, d=120, e=150, f=23;
    int *x = NULL;
    
    queue= Queue_Create(6);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Enqueue(queue, &a) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &b) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &c) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &d) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &e) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &f) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(*x == 5);
    /* ASSERT_THAT(x == a); */
    Queue_Destroy(&queue, NULL);   
END_UNIT

UNIT(Queue_Dequeue_empty)
    Queue *queue = NULL;
    int a=5, b=8, c=9, d=120, e=150, f=23;
    int *x = NULL;
    
    queue= Queue_Create(6);
    ASSERT_THAT(queue != NULL);
    ASSERT_THAT(Queue_Enqueue(queue, &a) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &b) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &c) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &d) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &e) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Enqueue(queue, &f) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_UNDERFLOW);
    
    Queue_Destroy(&queue, NULL);
END_UNIT

UNIT(Queue_IsEmpty_Null_args)
    ASSERT_THAT(Queue_IsEmpty(NULL) == 1);
END_UNIT

UNIT(Queue_end_to_end)

    Queue *queue = NULL;
    int i, arr[]={5,10,8,9,14,28,4,74,50,66,98};
    int *x=NULL;
    
    queue= Queue_Create(12);
    
    for(i=0; i < 11; ++i)
    {
        ASSERT_THAT(Queue_Enqueue(queue, arr + i) == QUEUE_SUCCESS);
    }
    ASSERT_THAT(Queue_IsEmpty(queue) == 0);
    for(i=0; i < 11; ++i)
    {
        ASSERT_THAT(Queue_Dequeue(queue, (void**)&x) == QUEUE_SUCCESS);
        ASSERT_THAT(*x = arr[i]);
    }
    
    ASSERT_THAT(Queue_IsEmpty(queue) == 1);
    Queue_Destroy(&queue, NULL);
END_UNIT

TEST_SUITE(Test Queue)
	TEST(Queue_Create_Null_args)
    TEST(Queue_Create_creation_legal_values)
	TEST(Queue_Enqueue_Null_args)
	TEST(Queue_Enqueue_to_built_queue)
	TEST(Queue_Enqueue_to_full_queue)
	TEST(Queue_Dequeue_Null_args)
	TEST(Queue_Dequeue_element)
	TEST(Queue_Dequeue_empty)
	TEST(Queue_IsEmpty_Null_args)
    /* Check inserts, extracts and again by peek, and size */
	TEST(Queue_end_to_end)
END_SUITE



