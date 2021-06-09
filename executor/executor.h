#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include  <stdlib.h> /*size_t*/
#include <time.h> /* clock_gettime */

/** 
 * @brief Create a periodic task Executor.
 */ 

typedef struct Executor Executor;
typedef int (*taskFunc)(void* _context);

typedef enum
{
    EXECUTOR_SUCCESS = 0,
	EXECUTOR__NOT_INITIALIZED,
	EXECUTOR__ALLOCATION_FAILED
}ExecutorErr;

/**  
 * @brief Apply an Executor for running tasks.  
 * @param[in] _less - comparison function for the heap
 * @return Executor * - on success
 * @retval NULL on fail 
 */
Executor* Executor_Create();

/**  
 * @brief Deallocate a previously allocated Executor
 * Frees the Executor.
 * @param[in] _exec - Executor to be deallocated.  On success will be nulled.
 * @return None
 */
void Executor_Destroy(Executor** _exec);

/**
 * @brief Add an tasks to the Executor preserving Executor property.  
 * @param[in] _exec - Executor to insert task to.
 * @param[in] _func - user function to insert as a task. can't be null
 * @param[in] _context - user _context to provide user function.
 * @param[in] _interval - user interval time for user function to run. can't be null
 * @return success or error code 
 * @retval Executor_SUCCESS  on success
 * @retval Executor_NOT_INITIALIZED  error, Executor not initialized
 * @retval Executor_REALLOCATION_FAILED error, Executor could not reallocate underlying vector 
 */
ExecutorErr Executor_AddTask(Executor* _exec , taskFunc _func , void* _context, double _interval);

/**
 * @brief Run the all tasks in the Given Executor.  
 * @param[in] _exec - Executor .
 * @return size_t - number of remaining tasks.  
 */
size_t Executor_Run(Executor* _exec);

/**
 * @brief Pause the Executor.  
 * @param[in] _exec - Executor .
 * @return success or error code 
 * @retval Executor_SUCCESS  on success
 * @retval Executor_NOT_INITIALIZED  error, Executor not initialized
 */
ExecutorErr Executor_Pause(Executor* _exec);


#endif


