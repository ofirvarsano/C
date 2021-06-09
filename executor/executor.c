#include "executor.h"
#include "task.h"
#include "../genericHeap/genericHeap.h"
#include <time.h>

struct Executor
{
	Heap* m_tasks;
	Vector* m_vec;
	int m_pauseFlag;
};

static void Executor_InitialRunTime(Vector* _vec);
static void Extract_And_Run(Executor* _exec);

Executor* Executor_Create()
{
	Executor* exec;
	exec = (Executor*)malloc(sizeof(Executor));
	if (exec == NULL)
	{
		return NULL;
	}
	exec->m_vec = Vector_Create(4,2);
	if (exec->m_vec == NULL)
	{
		free(exec);
		return NULL;
	}
	exec->m_tasks = Heap_Build(exec->m_vec, Task_Less);
	if (exec->m_tasks == NULL)
	{
		Vector_Destroy(&exec->m_vec, NULL);
		free(exec);
		return NULL;
	}
	exec->m_pauseFlag = 0;
	return exec;
}

void Executor_Destroy(Executor** _exec)
{
	if (_exec == NULL || *_exec == NULL)
	{
		return;
	}
	if ((*_exec)->m_tasks)
	{
		Heap_Destroy(&(*_exec)->m_tasks);
	}
	if ((*_exec)->m_vec)
	{
		Vector_Destroy(&(*_exec)->m_vec, Task_Destroy);
	}
	free(*_exec);
	*_exec = NULL;
}

ExecutorErr Executor_AddTask(Executor* _exec , taskFunc _func , void* _context, double _interval)
{
	Task* task;
	if (_exec == NULL || _func == NULL)
	{
		return EXECUTOR__NOT_INITIALIZED;
	}
	task = Task_Create(_func, _context, _interval);
	if (task == NULL)
	{
		return EXECUTOR__ALLOCATION_FAILED;
	}
	if (Heap_Insert(_exec->m_tasks, task) != HEAP_SUCCESS)
	{
		Task_Destroy(task);
		return EXECUTOR__ALLOCATION_FAILED;
	}
	return EXECUTOR_SUCCESS;
}

size_t Executor_Run(Executor* _exec)
{
	if (_exec == NULL || _exec->m_tasks == NULL)
	{
		return 0;
	}
	Executor_InitialRunTime(_exec->m_vec);
	while (Heap_Size(_exec->m_tasks) > 0 && _exec->m_pauseFlag ==0)
	{
		Extract_And_Run(_exec);
	}
	return Heap_Size(_exec->m_tasks);
}

static void Extract_And_Run(Executor* _exec)
{
	Task* task = (Task*)Heap_Extract(_exec->m_tasks);
	if ( task == NULL)
	{
		return;
	}
	if (Task_Run(task) == 0)
	{
		if (Heap_Insert(_exec->m_tasks, task) != HEAP_SUCCESS)
		{
			Task_Destroy(task);
		}
	}
	else
	{
		Task_Destroy(task);
	}
}

static void Executor_InitialRunTime(Vector* _vec)
{
	struct timespec currentTime;
	clock_gettime(CLOCK_REALTIME, &currentTime);
	Vector_ForEach(_vec, Task_Initial_Next_Run_Time, (void*)&currentTime); 
}

ExecutorErr Executor_Pause(Executor* _exec)
{
	if (_exec == NULL)
	{
		return EXECUTOR__NOT_INITIALIZED;
	}
	_exec->m_pauseFlag = 1;
	return EXECUTOR_SUCCESS;
}


