#ifndef _HEAP_H_
#define _HEAP_H_
#include "vector.h"

typedef struct Heap Heap;

/*
Description: Function creates a heap based on a given vector
function heapify the vector so its max value is at the first index
Input: a pointer to vector.
Output: a pointer to heap, NULL if allocation failed, or vector uninitialized.
Errors: non.
Complexity: O(n);
*/
Heap* HeapBuild(Vector* _vec);

/*
Description: Function free memory space reserved to the heap structure.
Input: a pointer to heap.
Output: none.
Errors: non.
Complexity: O(1);
*/
void HeapDestroy(Heap* _heap);

/*
Description: Function gets an int data, placing it in an appropriate spot in the heap.
Input: a pointer to heap, an int to be inserted.
Output: ADTErr.
Errors: ERR_NOT_INITIALIZED if heap pointer is invalid.
ERR_REALLOCATION_FAILED if realloc had to take place but failed,
ERR_OK for success.
Complexity: O(log n);
*/
ADTErr HeapInsert(Heap* _heap, int _data);

/*
Description: Function take the max value of the heap and storing a copy of it in a variable outside the function, while leaving the heap intact.
Input: a pointer to heap, a pointer to int.
Output: ADTErr.
Errors: ERR_NOT_INITIALIZED, if the pointers inserted as arguments are invalid.
ERR_UNDERFLOW if heap is empty.
Complexity: O(1);
*/
ADTErr HeapMax(Heap* _heap, int* _data);

/*
Description: Function take the max value of the heap and storing it in a variable outside the function, altering the heap as needed. 
Input: a pointer to heap, a pointer to int.
Output: ADTErr.
Errors: ERR_NOT_INITIALIZED, if the pointers inserted as arguments are invalid, ERR_UNDERFLOW if the heap is empty.
Complexity: O(log n);
*/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/*
Description: Function returns the number of items in the heap. 0 if heap not initialized.
Input: a pointer to heap.
Output: integer.
Errors: non.
Complexity: O(1);
*/
int HeapItemsNum(Heap* _heap);

/*
Description: Function prints the heap.
Input: a pointer to heap.
Output: non.
Errors: non.
Complexity: O(n);
*/
void HeapPrint(Heap* _heap);

#endif
