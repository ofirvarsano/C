#include "list.h"
#include "listErrors.h"
#include <stdio.h>
#include <stdlib.h>

/* ListCreate tests */

void test1()
{
	List* list = ListCreate();
	if(NULL == list)
	{
		printf("ListCreate FAIL\n");
	}
	else
	{
		printf("ListCreate PASS\n");
		ListDestroy(list);
	}
}

/* ListDestroy tests */

void test2()
{
	List* list = ListCreate();
	ListDestroy(list);
	printf("ListDestroy PASS\n");
}

void test3()
{
	List* list = ListCreate();
	ListDestroy(list);
	ListDestroy(list);
	printf("double ListDestroy PASS\n");
}

void test4()
{
	ListDestroy(NULL);
	printf("ListDestroy NULL PASS\n");
}

/* ListPushHead tests */

void test5()
{
	List* list = ListCreate();
	if(ListPushHead(list,3) == ERR_OK)
	{
		printf("ListPushHead(list,3) PASS\n");
		ListDestroy(list);
	}
	else
	{
		printf("ListPushHead(list,3) FAIL\n");
		ListDestroy(list);
	}
}

void test6()
{
	if(ListPushHead(NULL,3) == ERR_NOT_INITIALIZED)
	{
		printf("ListPushHead NULL PASS\n");
	}
	else
	{
		printf("ListPushHead NULL FAIL\n");
	}
}

void test7()
{
	int data;
	List* list = ListCreate();
	if(ListPushHead(list,3) == ERR_OK)
	{
		ListPopHead(list,&data);
		if(data == 3)
		{
			printf("ListPushHead(list,3) PASS\n");
			ListDestroy(list);
		}
		else
		{
			printf("ListPushHead(list,3) FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPushHead(list,3) FAIL\n");
		ListDestroy(list);
	}
}

void test8()
{
	int data;
	List* list = ListCreate();
	if(ListPushHead(list,3) == ERR_OK)
	{
		if(ListPushHead(list,4) == ERR_OK)
		{
			ListPopHead(list,&data);
			ListPopHead(list,&data);
			if(data == 3)
			{
				printf("double ListPushHead(list,3) PASS\n");
				ListDestroy(list);
			}
			else
			{
				printf("ListPushHead(list,3) FAIL\n");
				ListDestroy(list);
			}
		}
		else
		{
			printf("ListPushHead(list,3) FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPushHead(list,3) FAIL\n");
		ListDestroy(list);
	}
}

/* ListPopHead tests */

void test9()
{
	int data;
	if(ListPopHead(NULL,&data) == ERR_NOT_INITIALIZED)
	{
		printf("ListPopHead NULL PASS\n");
	}
	else
	{
		printf("ListPopHead NULL FAIL\n");
	}
}

void test10()
{
	int data;
	List* list = ListCreate();
	if(ListPopHead(list,&data) == ERR_UNDERFLOW)
	{
		printf("ListPopHead NULL PASS\n");
		ListDestroy(list);
	}
	else
	{
		printf("ListPopHead NULL FAIL\n");
		ListDestroy(list);
	}
}

void test11()
{
	int data;
	List* list = ListCreate();
	ListPushHead(list,4);
	if(ListPopHead(list,&data) == ERR_OK)
	{
		if(ListIsEmpty(list))
		{
			printf("ListPopHead NULL PASS\n");
			ListDestroy(list);
		}
		else
		{
			printf("ListPopHead NULL FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPopHead NULL FAIL\n");
		ListDestroy(list);
	}
}

/* ListPushTail tests */

void test12()
{
	List* list = ListCreate();
	if(ListPushTail(list,3) == ERR_OK)
	{
		printf("ListPushTail(list,3) PASS\n");
		ListDestroy(list);
	}
	else
	{
		printf("ListPushTail(list,3) FAIL\n");
		ListDestroy(list);
	}
}

void test13()
{
	if(ListPushTail(NULL,3) == ERR_NOT_INITIALIZED)
	{
		printf("ListPushTail NULL PASS\n");
	}
	else
	{
		printf("ListPushTail NULL FAIL\n");
	}
}

void test14()
{
	int data;
	List* list = ListCreate();
	if(ListPushTail(list,3) == ERR_OK)
	{
		ListPopTail(list,&data);
		if(data == 3)
		{
			printf("ListPushTail(list,3) PASS\n");
			ListDestroy(list);
		}
		else
		{
			printf("ListPushTail(list,3) FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPushTail(list,3) FAIL\n");
		ListDestroy(list);
	}
}

void test15()
{
	int data;
	List* list = ListCreate();
	if(ListPushTail(list,3) == ERR_OK)
	{
		if(ListPushTail(list,4) == ERR_OK)
		{
			ListPopTail(list,&data);
			ListPopTail(list,&data);
			if(data == 3)
			{
				printf("double ListPushTail(list,3) PASS\n");
				ListDestroy(list);
			}
			else
			{
				printf("ListPushTail(list,3) FAIL\n");
				ListDestroy(list);
			}
		}
		else
		{
			printf("ListPushTail(list,3) FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPushTail(list,3) FAIL\n");
		ListDestroy(list);
	}
}

/* ListPopTail */

void test16()
{
	int data;
	if(ListPopTail(NULL,&data) == ERR_NOT_INITIALIZED)
	{
		printf("ListPopTail NULL PASS\n");
	}
	else
	{
		printf("ListPopTail NULL FAIL\n");
	}
}

void test17()
{
	int data;
	List* list = ListCreate();
	if(ListPopTail(list,&data) == ERR_UNDERFLOW)
	{
		printf("ListPopTail PASS\n");
		ListDestroy(list);
	}
	else
	{
		printf("ListPopTail FAIL\n");
		ListDestroy(list);
	}
}

void test18()
{
	int data;
	List* list = ListCreate();
	ListPushTail(list,4);
	if(ListPopTail(list,&data) == ERR_OK)
	{
		if(ListIsEmpty(list))
		{
			printf("ListPopTail PASS\n");
			ListDestroy(list);
		}
		else
		{
			printf("ListPopTail FAIL\n");
			ListDestroy(list);
		}
	}
	else
	{
		printf("ListPopTail FAIL\n");
		ListDestroy(list);
	}
}

/* ListIsEmpty tests */

void test19()
{
	int data;
	List* list = ListCreate();
	if(ListIsEmpty(list))
	{
		printf("ListIsEmpty PASS\n");
	}
	else
	{
		printf("ListIsEmpty FAIL\n");
	}
	ListPushTail(list,4);
	if(!ListIsEmpty(list))
	{
		printf("ListIsEmpty PASS\n");
	}
	else
	{
		printf("ListIsEmpty FAIL\n");
	}
	if(ListPopTail(list,&data) == ERR_OK)
	{
		if(ListIsEmpty(list))
		{
			printf("ListIsEmpty PASS\n");
		}
		else
		{
			printf("ListIsEmpty FAIL\n");
		}
	}
	else
	{
		printf("ListIsEmpty FAIL\n");
	}
	ListDestroy(list);
}

void test20()
{
	if(ListIsEmpty(NULL))
	{
		printf("ListIsEmpty PASS\n");
	}
	else
	{
		printf("ListIsEmpty FAIL\n");
	}
}

/* ListCountItems tests */

void test21()
{
	if(ListCountItems(NULL) == 0)
	{
		printf("ListCountItems PASS\n");
	}
	else
	{
		printf("ListCountItems FAIL\n");
	}
}

void test22()
{
	List* list = ListCreate();
	if(ListCountItems(list) == 0)
	{
		printf("ListCountItems PASS\n");
	}
	else
	{
		printf("ListCountItems FAIL\n");
	}
	ListDestroy(list);
}

void test23()
{
	int data;
	List* list = ListCreate();
	ListPushTail(list,4);
	ListPushHead(list,4);
	if(ListCountItems(list) == 2)
	{
		printf("ListCountItems PASS\n");
	}
	else
	{
		printf("ListCountItems FAIL\n");
	}
	ListPopTail(list,&data);
	ListPopHead(list,&data);
	if(ListCountItems(list) == 0)
	{
		printf("ListCountItems PASS\n");
	}
	else
	{
		printf("ListCountItems FAIL\n");
	}
	ListDestroy(list);
}

/* ListPrint tests */

void test24()
{
	int data;
	List* list = ListCreate();
	ListPushTail(list,4);
	ListPopHead(list,&data);
	if(data == 4)
	{
		printf("ListPushTail ListPopHead PASS\n");
	}
	else
	{
		printf("ListPushTail ListPopHead FAIL\n");
	}
	ListDestroy(list);
}

void test25()
{
	int data;
	List* list = ListCreate();
	ListPushTail(list,4);
	ListPrint(list);
	printf("ListPrint 4 PASS\n");
	ListPopHead(list,&data);
	ListPrint(list);
	printf("ListPrint PASS\n");
	ListDestroy(list);
}

void test26()
{
	List* list = ListCreate();
	ListPrint(list);
	printf("ListPrint PASS\n");
	ListDestroy(list);
}

void test27()
{
	ListPrint(NULL);
	printf("ListPrint PASS\n");
}

void test28()
{
	List* list = ListCreate();
	ListPushTail(list,4);
	ListPushHead(list,5);
	ListPrint(list);
	printf("ListPrint 5 4 PASS\n");
	ListDestroy(list);
}

void test29()
{
	List* list = ListCreate();
	ListPushTail(list,4);
	ListPushHead(list,5);
	ListPrint(list);
	ListPrint(list);
	printf("double ListPrint 5 4 PASS\n");
	ListDestroy(list);
}

int main()
{
	/* ListCreate tests */
	test1();
	
	/* ListDestroy tests */
	test2();
	test3();
	test4();
	/* ListPushHead tests */
	test5();
	test6();
	test7();
	test8();
	/* ListPopHead tests */
	test9();
	test10();
	test11();
	/* ListPushTail tests */
	test12();
	test13();
	test14();
	test15();
	/* ListPopTail */
	test16();
	test17();
	test18();
	/* ListIsEmpty tests */
	test19();
	test20();
	/* ListCountItems tests */
	test21();
	test22();
	test23();
	/* ListPrint tests */
	test24();
	test25();
	test26();
	test27();
	test28();
	test29();
	
	return 0;
}








