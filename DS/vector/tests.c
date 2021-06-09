#include "vector.h"
#include <stdio.h>

/* VectorCreate tests */
ADTErr VectorGetLast(Vector* _vector,int* _item);

void test1()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(8,5);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(8,5) FAIL\n");
	}
	else
	{
		printf("VectorCreate(8,5) PASS\n");
		VectorDestroy(vecPtr);
	}
}

void test2()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(0,5);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(0,5) FAIL\n");
	}
	else
	{
		printf("VectorCreate(0,5) PASS\n");
		VectorDestroy(vecPtr);
	}
}

void test3()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(5,0);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(5,0) PASS\n");
	}
	else
	{
		printf("VectorCreate(5,0) FAIL\n");
		VectorDestroy(vecPtr);
	}
}

void test4()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(0,0);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(0,0) PASS\n");
	}
	else
	{
		printf("VectorCreate(0,0) FAIL\n");
		VectorDestroy(vecPtr);
	}
}

void test5()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(-1,3);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(-1,3) PASS\n");
	}
	else
	{
		printf("VectorCreate(-1,3) FAIL\n");
		VectorDestroy(vecPtr);
	}
}

/* VectorDestroy tests */

void test6()
{
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(8,5);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(8,5) FAIL\n");
	}
	VectorDestroy(vecPtr);
	printf("VectorDestroy PASS\n");
}

void test7()
{
	Vector* vecPtr = NULL;
	VectorDestroy(vecPtr);
	printf("VectorDestroy NULL PASS\n");
}

/* VectorAddEnd tests */

void test8()
{
	ADTErr err1;
	Vector* vecPtr = NULL;
	int item;
	vecPtr = VectorCreate(2,2);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(2,2) FAIL\n");
		exit(0);
	}
	err1 = VectorAddEnd(vecPtr, 5);
	VectorGet(vecPtr,0,&item);
	if(err1 == ERR_OK)
	{
		VectorGetLast(vecPtr, &item);
		if(item == 5)
		{
			printf("VectorAddEnd(vecPtr, 5) PASS\n");
		}
	}
	else
	{
		printf("VectorAddEnd(vecPtr, 5) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

void test9()
{
	ADTErr err1;
	Vector* vecPtr = NULL;
	err1 = VectorAddEnd(vecPtr, 5);
	if(err1 == ERR_NOT_INITIALIZED)
	{
		printf("VectorAddEnd(NULL, 5) PASS\n");
	}
	else
	{
		VectorDestroy(vecPtr);
		printf("VectorAddEnd(NULL, 5) FAIL\n");
	}
}

void test10()
{
	ADTErr err1;
	Vector* vecPtr = NULL;
	int item;
	vecPtr = VectorCreate(0,2);
	if(vecPtr == NULL)
	{
		printf("VectorCreate(0,2) FAIL\n");
		exit(0);
	}
	err1 = VectorAddEnd(vecPtr, 5);
	if(err1 == ERR_REALLOCATION_FAILED)
	{
		printf("VectorAddEnd(vecPtr, 5) FAIL ERR_REALLOCATION_FAILED\n");
	}
	if(err1 == ERR_OK)
	{
		VectorGetLast(vecPtr, &item);
		if(item == 5)
		{
			printf("VectorAddEnd(vecPtr, 5) PASS\n");
		}
	}
	else
	{
		printf("VectorAddEnd(vecPtr, 5) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

/* VectorDeleteEnd tests */

void test11()
{
	ADTErr err1;
	int item;
	Vector* vecPtr = NULL;
	err1 = VectorDeleteEnd(vecPtr, &item);
	if(err1 == ERR_NOT_INITIALIZED)
	{
		printf("VectorDeleteEnd(NULL, &item) PASS\n");
	}
	else
	{
		VectorDestroy(vecPtr);
		printf("VectorDeleteEnd(NULL, &item) FAIL\n");
	}
}

void test12()
{
	ADTErr err1;
	int item;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	err1 = VectorDeleteEnd(vecPtr, &item);
	if(err1 == ERR_UNDERFLOW)
	{
		printf("VectorDeleteEnd(vecPtr, &item) PASS\n");
	}
	else
	{
		printf("VectorDeleteEnd(vecPtr, &item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

void test13()
{
	ADTErr err1;
	int item;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 5);
	err1 = VectorDeleteEnd(vecPtr, &item);
	if(err1 == ERR_OK)
	{
		if(item == 5)
		{
			printf("VectorDeleteEnd(vecPtr, &item) PASS\n");
		}
		else
		{
			printf("VectorDeleteEnd(vecPtr, &item) FAIL\n");
		}
	}
	else
	{
		printf("VectorDeleteEnd(vecPtr, &item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

/* VectorItemsNum tests */
void test14()
{
	ADTErr err1;
	int num;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 5);
	err1 = VectorItemsNum(vecPtr,&num);
	if(err1 == ERR_OK)
	{
		if(num == 1)
		{
			printf("VectorItemsNum(vecPtr,&num) PASS\n");
		}
		else
		{
			printf("VectorItemsNum(vecPtr,&num) FAIL\n");
		}
	}
	else
	{
		printf("VectorItemsNum(vecPtr,&num) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

void test15()
{
	ADTErr err1;
	int num;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	err1 = VectorItemsNum(vecPtr,&num);
	if(err1 == ERR_OK)
	{
		if(num == 0)
		{
			printf("VectorItemsNum(vecPtr,&num) PASS\n");
		}
		else
		{
			printf("VectorItemsNum(vecPtr,&num) FAIL\n");
		}
	}
	else
	{
		printf("VectorItemsNum(vecPtr,&num) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

/* VectorGet tests */

void test16()
{
	ADTErr err;
	int item;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 5);
	err = VectorGet(vecPtr,1,&item);
	if(err == ERR_WRONG_INDEX)
	{
		printf("VectorGet(vecPtr,1,&item) PASS\n");
	}
	else
	{
		printf("VectorGet(vecPtr,1,&item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

void test17()
{
	ADTErr err;
	int item;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 8);
	VectorAddEnd(vecPtr, 5);
	err = VectorGet(vecPtr,1,&item);
	if(err == ERR_OK)
	{
		if(item == 5)
		{
			printf("VectorGet(vecPtr,1,&item) PASS\n");
		}
		else
		{
			printf("VectorGet(vecPtr,1,&item) FAIL\n");
		}
	}
	else
	{
		printf("VectorGet(vecPtr,1,&item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

/* VectorSet tests */

void test18()
{
	ADTErr err;
	int item = 5;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 5);
	err = VectorSet(vecPtr,1,item);
	if(err == ERR_WRONG_INDEX)
	{
		printf("VectorSet(vecPtr,1,&item) PASS\n");
	}
	else
	{
		printf("VectorSet(vecPtr,1,&item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

void test19()
{
	ADTErr err;
	int result;
	int item = 5;
	Vector* vecPtr = NULL;
	vecPtr = VectorCreate(2,2);
	VectorAddEnd(vecPtr, 2);
	err = VectorSet(vecPtr,0,item);
	if(err == ERR_OK)
	{
		VectorGet(vecPtr,0,&result);
		if(item == result)
		{
			printf("VectorSet(vecPtr,0,&item) PASS\n");
		}
		else
		{
			printf("VectorSet(vecPtr,0,&item) FAIL\n");
		}
	}
	else
	{
		printf("VectorSet(vecPtr,0,&item) FAIL\n");
	}
	VectorDestroy(vecPtr);
}

int main()
{
	/* VectorCreate tests */
	test1();
	test2();
	test3();
	test4();
	test5();
	/* VectorDestroy tests */
	test6();
	test7();
	/* VectorAddEnd tests */
	test8();
	test9();
	test10();
	/* VectorDeleteEnd tests */
	test11();
	test12();
	test13();
	/* VectorItemsNum tests */
	test14();
	test15();
	/* VectorGet tests */
	test16();
	test17();
	/* VectorSet tests */
	test18();
	test19();
	
	return 0;
}
