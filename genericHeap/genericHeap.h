#ifndef __HEAP_H__
#define __HEAP_H__
#include "../genericVector/genericVector.h"

/** 
 * @brief Create a Binary heap generic data type over a generic vector data type.
 */ 

typedef enum Heap_ResultCode
{
	HEAP_SUCCESS = 0,
	HEAP_NOT_INITIALIZED,
	HEAP_REALLOCATION_FAILED
}Heap_ResultCode;

typedef struct Heap Heap;

typedef int	(*LessThanComparator)(const void *_left, const void *_right);

/**  
 * @brief Apply a heap policy over a Vector container.  
 * @param[in] _vector - Vector that hold the elements, must be initialized
 * @param[in] _pfLess - A less than comparator to be used to compare elements 
 * @return Heap * - on success
 * @retval NULL on fail 
 *
 * @warning allocating and freeing the underlying vector is user responsibility. 
 * as long as vector is under the heap control, user should not access the vector directly
 */
Heap* Heap_Build(Vector* _vector, LessThanComparator _pfLess);

/**
 * @brief Deallocate a previously allocated heap
 * Frees the heap but not the underlying vector  
 * @param[in] _heap - Heap to be deallocated. On success will be nulled.
 * @return Underlying vector
 */
Vector* Heap_Destroy(Heap** _heap);

/**
 * @brief Add an element to the Heap preserving heap property.  
 * @param[in] _heap - Heap to insert element to.
 * @param[in] _element - Element to insert. can't be null
 * @return success or error code 
 * @retval HEAP_SUCCESS  on success
 * @retval HEAP_NOT_INITIALIZED  error, heap not initilized
 * @retval HEAP_REALLOCATION_FAILED error, heap could not reallocate underlying vector 
 */

Heap_ResultCode Heap_Insert(Heap* _heap, void* _element);

/**
 * @brief Peek at element on top of heap without extracting it.  
 * @param[in] _heap - Heap to peek at.
 * @return pointer to element, can be null if heap is empty or on error
 */

const void* Heap_Peek(const Heap* _heap);

/**  
 * @brief Extract element on top of heap and remove it.  
 * @param[in] _heap - Heap to extract from.
 * @return pointer to element, can be null if heap is empty. 
 */

void* Heap_Extract(Heap* _heap);

/**  
 * @brief Get the current size (number of elements) in the heap.  
 * @param[in] _heap - the Heap.
 * @return number of elements or zero if empty. 
 */

size_t Heap_Size(const Heap* _heap);

#endif /*__HEAP_H__*/





