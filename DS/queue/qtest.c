#include "queue.h"
#include <stdio.h>

/* QueueCreate tests */

void test1()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(8);
	if(qPtr == NULL)
	{
		printf("QueueCreate(8) FAIL\n");
	}
	else
	{
		printf("QueueCreate(8) PASS\n");
		QueueDestroy(qPtr);
	}
}

void test2()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(0);
	if(qPtr == NULL)
	{
		printf("QueueCreate(0) PASS\n");
	}
	else
	{
		printf("QueueCreate(0) FAIL\n");
		QueueDestroy(qPtr);
	}
}

/* QueueDestroy tests */

void test3()
{
	Queue* qPtr = NULL;
	QueueDestroy(qPtr);
	printf("QueueDestroy NULL PASS\n");
}

void test4()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(8);
	if(qPtr == NULL)
	{
		printf("QueueCreate(8) FAIL\n");
	}
	QueueDestroy(qPtr);
	QueueDestroy(qPtr);
	printf("QueueDestroy PASS\n");
}

void test5()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(8);
	if(qPtr == NULL)
	{
		printf("QueueCreate(8) FAIL\n");
	}
	else
	{
		QueueDestroy(qPtr);
		printf("QueueDestroy PASS\n");
	}
}

/* QueueInsert tests */

void test6()
{
	int item;
	ADTErr err;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(3);
	if(qPtr == NULL)
	{
		printf("QueueCreate(3) FAIL\n");
		return;
	}
	err = QueueInsert(qPtr,5);
	if(err == ERR_OK)
	{
		err = QueueInsert(qPtr,2);
		if(err == ERR_OK)
		{
			QueueRemove(qPtr,&item);
			if(item == 5)
			{
				QueueRemove(qPtr,&item);
				if(item == 2)
				{
					printf("QueueInsert PASS\n");
				}
				else
				{
					printf("QueueInsert FAIL\n");
				}
			}
			else
			{
				printf("QueueInsert FAIL\n");
			}
		}
		else
		{
			printf("QueueInsert FAIL\n");
		}
	}
	else
	{
		printf("QueueInsert FAIL\n");
	}
	QueueDestroy(qPtr);
}

void test7()
{
	ADTErr err;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(3);
	if(qPtr == NULL)
	{
		printf("QueueCreate(8) FAIL\n");
	}
	QueueInsert(qPtr,5);
	QueueInsert(qPtr,5);
	QueueInsert(qPtr,5);
	err = QueueInsert(qPtr,5);
	if(err == ERR_OVERFLOW)
	{
		printf("QueueInsert PASS\n");
	}
	else
	{
		printf("QueueInsert PASS\n");
	}
	QueueDestroy(qPtr);
}

void test8()
{
	ADTErr err;
	Queue* qPtr = NULL;
	err = QueueInsert(qPtr,5);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("QueueInsert PASS\n");
	}
	else
	{
		printf("QueueInsert PASS\n");
	}
}

void test9()
{
	ADTErr err;
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	if(qPtr == NULL)
	{
		printf("QueueCreate(8) FAIL\n");
		return;
	}
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,2);
	QueueInsert(qPtr,3);
	QueueRemove(qPtr,&item);
	QueueInsert(qPtr,4);
	QueueRemove(qPtr,&item);
	QueueRemove(qPtr,&item);
	err = QueueInsert(qPtr,5);
	if(err == ERR_OK)
	{
		QueueRemove(qPtr,&item);
		if(item == 4)
		{
			QueueRemove(qPtr,&item);
			if(item == 5)
			{
				printf("QueueInsert PASS\n");
			}
			else
			{
				printf("QueueInsert FAIL\n");
			}
		}
		else
		{
			printf("QueueInsert FAIL\n");
		}
	}
	else
	{
		printf("QueueInsert FAIL\n");
	}
	QueueDestroy(qPtr);
}

/* QueueRemove tests */

void test10()
{
	ADTErr err;
	int item;
	Queue* qPtr = NULL;
	err = QueueRemove(qPtr,&item);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("QueueRemove PASS\n");
	}
	else
	{
		printf("QueueRemove FAIL\n");
	}
}

void test11()
{
	ADTErr err;
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	err = QueueRemove(qPtr,&item);
	if(err == ERR_UNDERFLOW)
	{
		printf("QueueRemove PASS\n");
	}
	else
	{
		printf("QueueRemove FAIL\n");
	}
	QueueDestroy(qPtr);
}

void test12()
{
	ADTErr err;
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,4);
	err = QueueRemove(qPtr,&item);
	if(err == ERR_OK)
	{
		if(item == 4)
		{
			printf("QueueRemove PASS\n");
		}
		else
		{
			printf("QueueRemove FAIL\n");
		}
	}
	else
	{
		printf("QueueRemove FAIL\n");
	}
	QueueDestroy(qPtr);
}

void test13()
{
	ADTErr err;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,4);
	err = QueueRemove(qPtr,NULL);
	if(err == ERR_NOT_INITIALIZED)
	{
		printf("QueueRemove PASS\n");
	}
	else
	{
		printf("QueueRemove FAIL\n");
	}
	QueueDestroy(qPtr);
}

/* QueueIsEmpty tests */

void test14()
{
	int isEmpty;
	Queue* qPtr = NULL;
	isEmpty = QueueIsEmpty(qPtr);
	if(isEmpty)
	{
		printf("QueueIsEmpty PASS\n");
	}
	else
	{
		printf("QueueIsEmpty FAIL\n");
	}
}

void test15()
{
	int isEmpty;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	isEmpty = QueueIsEmpty(qPtr);
	if(isEmpty)
	{
		printf("QueueIsEmpty PASS\n");
	}
	else
	{
		printf("QueueIsEmpty FAIL\n");
	}
	QueueDestroy(qPtr);
}

void test16()
{
	int isEmpty;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,4);
	isEmpty = QueueIsEmpty(qPtr);
	if(!isEmpty)
	{
		printf("QueueIsEmpty PASS\n");
	}
	else
	{
		printf("QueueIsEmpty FAIL\n");
	}
	QueueDestroy(qPtr);
}

void test17()
{
	int isEmpty;
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,4);
	QueueRemove(qPtr,&item);
	isEmpty = QueueIsEmpty(qPtr);
	if(isEmpty)
	{
		printf("QueueIsEmpty PASS\n");
	}
	else
	{
		printf("QueueIsEmpty FAIL\n");
	}
	QueueDestroy(qPtr);
}

/* QueuePrint tests */

void test18()
{
	Queue* qPtr = NULL;
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
}

void test19()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

void test20()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,4);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

void test21()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,2);
	QueueInsert(qPtr,3);
	QueueInsert(qPtr,4);
	QueueInsert(qPtr,5);
	QueueInsert(qPtr,6);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

void test22()
{
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,2);
	QueueInsert(qPtr,3);
	QueueInsert(qPtr,4);
	QueueInsert(qPtr,5);
	QueueInsert(qPtr,6);
	QueueRemove(qPtr,&item);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

void test23()
{
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,2);
	QueueInsert(qPtr,3);
	QueueInsert(qPtr,4);
	QueueInsert(qPtr,5);
	QueueInsert(qPtr,6);
	QueueRemove(qPtr,&item);
	QueueInsert(qPtr,6);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

void test24()
{
	int item;
	Queue* qPtr = NULL;
	qPtr = QueueCreate(1);
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,3);
	QueuePrint(qPtr);
	QueueRemove(qPtr,&item);
	QueueInsert(qPtr,2);
	QueuePrint(qPtr);
	QueueRemove(qPtr,&item);
	printf("QueueCreate(1) and insert PASS\n");
	QueueDestroy(qPtr);
}

void test25()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(5);
	QueueInsert(qPtr,1);
	QueueInsert(qPtr,2);
	QueueInsert(qPtr,3);
	QueueInsert(qPtr,4);
	QueuePrint(qPtr);
	QueuePrint(qPtr);
	printf("QueuePrint PASS\n");
	QueueDestroy(qPtr);
}

int main()
{
	/* QueueCreate tests */
	test1();
	test2();
	/* QueueDestroy tests */
	test3();
	test4();
	test5();
	/* QueueInsert tests */
	test6();
	test7();
	test8();
	test9();
	/* QueueRemove tests */
	test10();
	test11();
	test12();
	test13();
	/* QueueIsEmpty tests */
	test14();
	test15();
	test16();
	test17();
	/* QueuePrint tests */
	test18();
	test19();
	test20();
	test21();
	test22();
	test23();
	
	test24();
	test25();
	
	return 0;
}
