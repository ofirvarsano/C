#include "vector.h"
#include "stack.h"
#include <stdio.h>

/* StackCreate tests */

void test1()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(8,5);
	if(stackPtr == NULL)
	{
		printf("StackCreate(8,5) FAIL\n");
	}
	else
	{
		printf("StackCreate(8,5) PASS\n");
		StackDestroy(stackPtr);
	}
}

void test2()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(8,0);
	if(stackPtr == NULL)
	{
		printf("StackCreate(8,0) PASS\n");
	}
	else
	{
		printf("StackCreate(8,0) FAIL\n");
		StackDestroy(stackPtr);
	}
}

/* StackDestroy tests */

void test3()
{
	Stack* stackPtr = NULL;
	StackDestroy(stackPtr);
	printf("StackDestroy NULL PASS\n");
}

void test4()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr == NULL)
	{
		printf("StackCreate(2,2) FAIL\n");
	}
	StackDestroy(stackPtr);
	StackDestroy(stackPtr);
	printf("StackDestroy PASS\n");
}

void test5()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr == NULL)
	{
		printf("StackCreate(2,2) FAIL\n");
	}
	StackDestroy(stackPtr);
	printf("StackDestroy PASS\n");
}

/* StackPush tests */

void test6()
{
	int item;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,5);
		StackTop(stackPtr,&item);
		if(item == 5)
		{
			printf("StackPush(stackPtr,5) PASS\n");
		}
		else
		{
			printf("StackPush(stackPtr,5) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackPush(stackPtr,5) FAIL\n");
	}
}

void test7()
{
	int item;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(0,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,5);
		StackTop(stackPtr,&item);
		if(item == 5)
		{
			printf("StackPush(stackPtr,5) PASS\n");
		}
		else
		{
			printf("StackPush(stackPtr,5) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackPush(stackPtr,5) FAIL\n");
	}
}

void test8()
{
	ADTErr err;
	Stack* stackPtr = NULL;
	err = StackPush(stackPtr,5);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("StackPush(stackPtr,5) PASS\n");
	}
	else
	{
		printf("StackPush(stackPtr,5) FAIL\n");
	}
}

/* StackPop tests */

void test9()
{
	int item;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,5);
		StackPop(stackPtr,&item);
		if(item == 5)
		{
			printf("StackPop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackPop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackPop(stackPtr,&item) FAIL\n");
	}
}

void test10()
{
	int item;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,5);
		StackPush(stackPtr,6);
		StackPush(stackPtr,7);
		StackPop(stackPtr,&item);
		if(item == 7)
		{
			StackPop(stackPtr,&item);
			if(item == 6)
			{
				StackPop(stackPtr,&item);
				if(item == 5)
				{
					printf("StackPop(stackPtr,&item) PASS\n");
				}
				else
				{
					printf("StackPop(stackPtr,&item) FAIL\n");
				}
			}
			else
			{
				printf("StackPop(stackPtr,&item) FAIL\n");
			}
		}
		else
		{
			printf("StackPop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackPop(stackPtr,&item) FAIL\n");
	}
}

void test11()
{
	int item;
	ADTErr err;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		err = StackPop(stackPtr,&item);
		if(err == ERR_UNDERFLOW)
		{
			printf("StackPop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackPop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackPop(stackPtr,&item) FAIL\n");
	}
}

void test17()
{
	int item;
	ADTErr err;
	Stack* stackPtr = NULL;
	err = StackPop(stackPtr,&item);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("StackPop(stackPtr,&item) PASS\n");
	}
	else
	{
		printf("StackPop(stackPtr,&item) FAIL\n");
		StackDestroy(stackPtr);
	}
}

void test18()
{
	ADTErr err;
	Stack* stackPtr = NULL;
	err = StackPop(stackPtr,NULL);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("StackPop(stackPtr,&item) PASS\n");
	}
	else
	{
		printf("StackPop(stackPtr,&item) FAIL\n");
	}
	StackDestroy(stackPtr);
}

/* StackTop tests */

void test12()
{
	int item;
	ADTErr err;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		err = StackTop(stackPtr,&item);
		if(err == ERR_UNDERFLOW)
		{
			printf("StackTop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackTop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackTop(stackPtr,&item) FAIL\n");
	}
}

void test13()
{
	int item;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,2);
		StackPush(stackPtr,5);
		StackTop(stackPtr,&item);
		if(item == 5)
		{
			printf("StackTop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackTop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackTop(stackPtr,&item) FAIL\n");
	}
}

void test14()
{
	int item1,item2;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,2);
		StackPush(stackPtr,5);
		StackTop(stackPtr,&item1);
		StackPop(stackPtr,&item2);
		if(item1 == item2)
		{
			printf("StackTop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackTop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackTop(stackPtr,&item) FAIL\n");
	}
}

void test19()
{
	ADTErr err;
	int item;
	Stack* stackPtr = NULL;
	err = StackTop(stackPtr,&item);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("StackTop(stackPtr,&item) PASS\n");
	}
	else
	{
		printf("StackTop(stackPtr,&item) FAIL\n");
		StackDestroy(stackPtr);
	}
}

void test20()
{
	ADTErr err;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		err = StackTop(stackPtr,NULL);
		if(err == ERR_NOT_INITIALIZED)
		{
			printf("StackTop(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackTop(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackTop(stackPtr,&item) FAIL\n");
	}
}

/* StackIsEmpty tests */

void test15()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		StackPush(stackPtr,2);
		if(StackIsEmpty(stackPtr))
		{
			printf("StackIsEmpty(stackPtr,&item) FAIL\n");
		}
		else
		{
			printf("StackIsEmpty(stackPtr,&item) PASS\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackIsEmpty(stackPtr,&item) FAIL\n");
	}		
}

void test16()
{
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(2,2);
	if(stackPtr != NULL)
	{
		if(StackIsEmpty(stackPtr))
		{
			printf("StackIsEmpty(stackPtr,&item) PASS\n");
		}
		else
		{
			printf("StackIsEmpty(stackPtr,&item) FAIL\n");
		}
		StackDestroy(stackPtr);
	}
	else
	{
		printf("StackIsEmpty(stackPtr,&item) FAIL\n");
	}		
}

int main()
{
	/* StackCreate tests */
	test1();
	test2();
	/* StackDestroy tests */
	test3();
	test4();
	test5();
	/* StackPush tests */
	test6();
	test7();
	test8();
	/* StackPop tests */
	test9();
	test10();
	test11();
	test17();
	test18();
	/* StackTop tests */
	test12();
	test13();
	test14();
	test19();
	test20();
	/* StackIsEmpty tests */
	test15();
	test16();
	
	return 0;
}
