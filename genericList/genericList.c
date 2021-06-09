#include "genericList.h"
#include "listStructs.h"
#include <stdlib.h>
#define MAGIC 34526

/* m_head->m_data of head and tail can be magic caus it is not in use, then MAGIC can be deleted */
List* List_Create(void)
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

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* current = NULL;
	if (_pList && *_pList && (*_pList)->m_magic == MAGIC)
	{
		current = (*_pList)->m_tail.m_prev;
		while (current->m_prev != NULL)
		{
			current = current->m_prev;
			if (_elementDestroy != NULL)
			{
				_elementDestroy(current->m_next->m_data);
			}
			free(current->m_next);
		}
		(*_pList)->m_magic = 0;
		free(*_pList);
		*_pList = NULL;
	}
	return;
}

List_Result InsertBefore(Node* _t, void* _item)
{
	Node* newNode = NULL;
	if(NULL == _item)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = malloc(sizeof(Node));
	if(NULL == newNode)
	{
		return LIST_ALLOCATION_ERROR;
	}
	newNode->m_data = _item;
	
	newNode->m_prev = _t->m_prev;
	newNode->m_next = _t;
	_t->m_prev->m_next = newNode;
	_t->m_prev = newNode;
	
	return LIST_SUCCESS;
}

List_Result List_PushHead(List* _list, void* _item)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	return InsertBefore(_list->m_head.m_next, _item);
}

List_Result List_PushTail(List* _list, void* _item)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	return InsertBefore(&_list->m_tail, _item);
}

List_Result Remove(Node* _toRemove, void** _pItem)
{
	if(NULL == _pItem)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	_toRemove->m_next->m_prev = _toRemove->m_prev;
	_toRemove->m_prev->m_next = _toRemove->m_next;

	*_pItem = _toRemove->m_data;
	free(_toRemove);
	return LIST_SUCCESS;
}

List_Result List_PopHead(List* _list, void** _pItem)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_UNDERFLOW_ERROR;
	}
	return Remove(_list->m_head.m_next, _pItem);
}

List_Result List_PopTail(List* _list, void** _pItem)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_UNDERFLOW_ERROR;
	}
	return Remove(_list->m_tail.m_prev, _pItem);
}

size_t List_Size(const List* _list)
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
		++count;
		current = current->m_next;
	}
	return count;
}


