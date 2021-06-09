#ifndef __TASK_H__
#define __TASK_H__

#include  <stdlib.h> /*size_t*/
#define _GNU_SOURCE 1
#include <time.h> /* clock_gettime */
#undef _GNU_SOURCE
/** 
 * @brief Create a task
 */ 

typedef struct Task Task;

typedef enum
{
    TASK_SUCCESS = 0,
	TASK_NOT_INITIALIZED,
	TASK_REALLOCATION_FAILED
}ErrResult;

/**  
 * @brief Create a new task with given user parameters.  
 * @param[in] _func - user function to insert as a task. can't be null
 * @param[in] _context - user _context to provide the user function.
 * @param[in] _interval - user interval time for user function to run. can't be null
 * @return Task * - on success
 * @retval NULL on fail 
 *
 * @warning allocating and freeing the underlying vector is user responsibility.
 * as long as vector is under the EXECUTER control, user should not access the vector directly*/
Task* Task_Create(int (*_func)(void* _context), void* _context, double _interval);

/**  
 * @brief Deallocate a previously allocated task
 * Frees the task.
 * @param[in] _task - task to be deallocated.  On success will be nulled.
 * @return None
 */
void Task_Destroy(void* _task);

/**
 * @brief run the task
 * @param[in] _task.
 * @return int - 0 if needs to be executed again otherwise stop
 */
int Task_Run(Task* _task);

/* comparison function */
int Task_Less(const void* _task1, const void* _task2);

/* initial first run time for element*/
int Task_Initial_Next_Run_Time(void* _element, size_t _index, void* _context);

#endif /* __TASK_H__ */



