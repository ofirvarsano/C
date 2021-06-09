#include "personList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person globalP[4]= {{20,"ofir",25,NULL},{30,"p2",26,NULL}};

/* ListInsertHead tests */

void test1()
{
	if(ListInsertHead(NULL,NULL) == NULL)
	{
		printf("ListInsertHead(NULL,NULL) PASS\n");
	}	
}

void test2()
{
	Person p;
	Person* result = NULL;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	result = ListInsertHead(NULL,&p);
	PrintList(result);
	printf("ListInsertHead(NULL,p) PASS\n");
}

void test3()
{
	Person p,p2;
	Person* result = NULL;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	
	p2.m_id = 30;
	strcpy(p2.m_name,"p2");
	p2.m_age = 26;
	p2.m_next = NULL;
	result = ListInsertHead(result,&p);
	result = ListInsertHead(result,&p2);
	PrintList(result);
	printf("double ListInsertHead(NULL,p) PASS\n");
}

/* ListRemoveHead tests */

void test4()
{
	Person* p2 = NULL;
	Person p;
	Person* result = NULL;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	result = ListInsertHead(result,&p);
	/* &globalP[0] */
	if(ListRemoveHead(NULL,&p2) == NULL)
	{
		printf("ListRemoveHead(NULL,&p2) PASS\n");
	}
	else
	{
		printf("ListRemoveHead(result,&p2) FAIL\n");
	}
}

void test5()
{
	Person p;
	Person* result = NULL;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	result = ListInsertHead(result,&p);
	if(ListRemoveHead(result,NULL) == result)
	{
		printf("ListRemoveHead(result,NULL) PASS\n");
	}
	else
	{
		printf("ListRemoveHead(result,NULL) FAIL\n");
	}
}

void test6()
{
	Person* p2 = NULL;
	Person p;
	Person* result = NULL;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	result = ListInsertHead(result,&p);
	if(ListRemoveHead(result,&p2) == NULL)
	{
		if(p2->m_id == 20)
		{
			printf("ListRemoveHead(result,&p2) PASS\n");
		}
		else
		{
			printf("ListRemoveHead(result,&p2) FAIL\n");
		}
	}
	else
	{
		printf("ListRemoveHead(result,&p2) FAIL\n");
	}
}

int main()
{
	/* ListInsertHead tests */
	test1();
	test2();
	test3();
	/* ListRemoveHead tests */
	test4();
	test5();
	test6();
/*
	Person* head = NULL;
	Person* temp = NULL;
	Person p;
	Person p2,p3,p4;
	p.m_id = 20;
	strcpy(p.m_name,"p1");
	p.m_age = 25;
	p.m_next = NULL;
	head = ListInsertHead(head,&p);
	PrintList(head);
	printf("\n\n");
	
	p2.m_id = 10;
	strcpy(p2.m_name,"p2");
	p2.m_age = 25;
	p2.m_next = NULL;
	head = ListInsertByKey(head,10,&p2);
	PrintList(head);
	printf("\n\n");
	
	p3.m_id = 30;
	strcpy(p3.m_name,"p3");
	p3.m_age = 25;
	p3.m_next = NULL;
	*/
	/*head = ListInsertByKey(head,30,&p3);
	PrintList(head);
	printf("\n\n");
	
	head = ListRemoveByKey(head,10,&temp);
	PrintList(head);
	printf("\n\n");
	printf("name: %s id: %d age: %d\n",temp->m_name,temp->m_id,temp->m_age);*/
	/*
	p4.m_id = 30;
	strcpy(p4.m_name,"p4");
	p4.m_age = 25;
	p4.m_next = NULL;
	head = ListInsertByKeyRec(head,30,&p4);
	PrintList(head);
	printf("\n\n");
	
	head = ListRemoveByKeyRec(head,30,&temp);
	PrintList(head);
	printf("\n\n");
	
	printf("name: %s id: %d age: %d\n",temp->m_name,temp->m_id,temp->m_age);
	*/
	/*Person* head;
	Person first,second,third;
	second.m_id = 222;
	strcpy(second.m_name,"abc");
	second.m_age = 26;
	second.m_next = NULL;
	first.m_id = 111;
	strcpy(first.m_name,"ofir");
	first.m_age = 25;
	first.m_next = &second;
	PrintList(&first);
	printf("\n\n");
	third.m_id = 333;
	strcpy(third.m_name,"ccc");
	third.m_age = 26;
	third.m_next = NULL;
	head = ListInsertHead(&first,&third);
	PrintList(head);
	*/

	return 0;
}
