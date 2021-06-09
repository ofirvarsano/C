#include <stdio.h>
#include <stdlib.h>
#include "../mu_test.h"
#include "executor.h"
#include "../genericHeap/genericHeap.h"
#include "../genericVector/genericVector.h"

typedef int (*userFunc)(void* _context);

int funcA(void* _context)
{
	printf("%s\n", "function A");
	--*(int*)_context;
	if(*(int*)_context > 0)
		return 0;
	else
		return 1;
}

int funcB(void* _context)
{
	static int b = 3;
	printf("%s\n", "function B");
	--b;
	return b ? 0 : 1;
}

int funcC(void* _context)
{
	static int c = 3;
	printf("%s\n", "function C");
	--c;
	return c ? 0 : 1;
}

int funcD(void* _context)
{
	static int d = 10;
	printf("%s\n", "function D");
	--d;
	return d ? 0 : 1;
}

int funcE(void* _context)
{
	static int e = 3;
	printf("%s\n", "function E");
	--e;
	return e ? 0 : 1;
}

int addTask(void* _context)
{
	printf("%s\n", "Add Task 'function C'");
	Executor_AddTask((Executor*)_context, funcC, NULL, 2);
	return 1;
}

int pauseTasks(void* _context)
{
	printf("%s\n", "Pause Tasks");
	Executor_Pause((Executor*)_context);
	return 1;
}

UNIT(exec_ok)
	int x = 5;
	Executor* exec = Executor_Create();
	ASSERT_THAT(exec != NULL);
	Executor_AddTask(exec, funcA, &x, 4.3);
	Executor_AddTask(exec, funcB, NULL, 3);
	Executor_AddTask(exec, funcE, NULL, 10);
	Executor_AddTask(exec, funcD, NULL, 8);
	Executor_AddTask(exec, addTask, exec, 4.3);
	Executor_AddTask(exec, pauseTasks, exec, 13);
	
	printf("remaining tasks = %ld\n", Executor_Run(exec));
	Executor_Destroy(&exec);
END_UNIT

TEST_SUITE(test EXECUTOR)
	TEST(exec_ok)
END_SUITE


