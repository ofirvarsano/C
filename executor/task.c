#include "task.h"
#include "my_time.h"

typedef int (*func)(void* _context);

struct Task
{
	func m_taskFunc;
	TaskTime m_interval;
	void* m_context;
	TaskTime m_nextRunTime;
};

Task* Task_Create(int (*_func)(void* _context), void* _context, double _interval)
{
	Task* newTask;
	if (_func == NULL || _interval <= 0)
	{
		return NULL;
	}
	newTask = (Task*)malloc(sizeof(Task));
	if (newTask == NULL)
	{
		return NULL;
	}
	newTask->m_taskFunc = _func;
	newTask->m_interval = Time_Convert(_interval);
	newTask->m_context = _context;
	newTask->m_nextRunTime = Time_CalcNextTime(newTask->m_interval);
	
	return newTask;
}

void Task_Destroy(void* _task)
{
	if ((Task*)_task)
	{
		free((Task*)_task);
	}
}

int Task_Run(Task* _task)
{
	int result;
	if (_task == NULL)
	{
		return 1;
	}
	Time_SleepUntill(_task->m_nextRunTime);
	result = _task->m_taskFunc(_task->m_context);
	_task->m_nextRunTime = Time_CalcNextTime(_task->m_interval);
	return result;
}

int Task_Initial_Next_Run_Time(void* _element, size_t _index, void* _context)
{
	if ((Task*)_element)
	{
		((Task*)_element)->m_nextRunTime = time_add(((Task*)_element)->m_interval, *(TaskTime*)_context);
	}
	return 1;
}

int Task_Less(const void* _task1, const void* _task2)
{
	if (_task1 && _task2)
	{
		return Time_IsLess(((Task*)_task1)->m_nextRunTime, ((Task*)_task2)->m_nextRunTime);
	}
	return 1;
}



