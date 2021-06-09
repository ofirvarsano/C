#include "list.h"
#include "listErrors.h"
#include <stdio.h>
#include <stdlib.h>
#define MAGIC 2345
#define TRUE 1
#define FALSE 0

struct Node
{
	int m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	int m_magic;
};

List* ListCreate(void)
{
	List* list = (List*)malloc(sizeof(List));
	if(NULL == list)
	{
		return NULL;
	}
	list->m_head.m_next = &list->m_tail;
	list->m_head.m_prev = NULL;
	list->m_tail.m_next = NULL;
	list->m_tail.m_prev = &list->m_head;
	list->m_magic = MAGIC;
	return list;
}

void ListDestroy(List* _list)
{
	Node* current = NULL;
	if(_list && _list->m_magic == MAGIC)
	{
		current = _list->m_tail.m_prev;
		while(current->m_prev != NULL)
		{
			current = current->m_prev;
			free(current->m_next);
		}
		_list->m_magic = 0;
		free(_list);
	}
}

static void Insert(Node* _p,Node* _t)
{
	_p->m_prev = _t->m_prev;
	_p->m_next = _t;
	_t->m_prev->m_next = _p;
	_t->m_prev =_p;
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* toAdd = NULL;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	toAdd = (Node*)malloc(sizeof(Node));
	if(NULL == toAdd)
	{
		return ERR_ALLOCATION_FAIL;
	}
	toAdd->m_data = _data;
	Insert(toAdd,_list->m_head.m_next);
	return ERR_OK;
}

ADTErr ListPushTail(List* _list, int _data)
{
	Node* toAdd = NULL;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	toAdd = (Node*)malloc(sizeof(Node));
	if(NULL == toAdd)
	{
		return ERR_ALLOCATION_FAIL;
	}
	toAdd->m_data = _data;
	Insert(toAdd,&_list->m_tail);
	return ERR_OK;
}

static void Remove(Node* _t)
{
	_t->m_next->m_prev = _t->m_prev;
	_t->m_prev->m_next = _t->m_next;
	free(_t);
}

ADTErr ListPopHead(List* _list, int* _data)
{
	Node* current = NULL;
	if(NULL == _list || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_UNDERFLOW;
	}
	current = _list->m_head.m_next;
	*_data = current->m_data;
	Remove(current);
	return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{
	Node* current = NULL;
	if(NULL == _list || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_UNDERFLOW;
	}
	current = _list->m_tail.m_prev;
	*_data = current->m_data;
	Remove(current);
	return ERR_OK;
}

size_t ListCountItems(List* _list)
{
	Node* current = NULL;
	size_t count = 0;
	if(NULL == _list)
	{
		return 0;
	}
	current = _list->m_head.m_next;
	while(current != &_list->m_tail)
	{
		count++;
		current = current->m_next;
	}
	return count;
}

int ListIsEmpty(List* _list)
{
	if(NULL == _list)
	{
		return TRUE;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return TRUE;
	}
	return FALSE;
}

void ListPrint(List* _list)
{
	Node* current = NULL;
	if(NULL == _list)
	{
		return;
	}
	current = _list->m_head.m_next;
	while(current != &_list->m_tail)
	{
		printf("data: %d\n",current->m_data);
		current = current->m_next;
	}
}

