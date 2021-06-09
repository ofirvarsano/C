#include "../listStructs.h"
#include "../genericList.h"
#include "list_itr.h"
#include <stdlib.h>

ListItr ListItr_Begin(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	return (ListItr)_list->m_head.m_next;
}

ListItr ListItr_End(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	return (ListItr)&_list->m_tail;
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return _a == _b;
}

ListItr ListItr_Next(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	if(((Node*)_itr)->m_next != NULL)
	{
		return (ListItr)(((Node*)_itr)->m_next);
	}
	return _itr;
}

ListItr ListItr_Prev(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	if(((Node*)_itr)->m_prev->m_prev != NULL)
	{
		return (ListItr)(((Node*)_itr)->m_prev);
	}
	return _itr;
}

void* ListItr_Get(ListItr _itr)
{
	if(_itr == NULL || ((Node*)_itr)->m_next == NULL)
	{
		return NULL;
	}
	return ((Node*)_itr)->m_data;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	void* toReturn = NULL;
	if(_itr == NULL || _element == NULL || ((Node*)_itr)->m_next == NULL)
	{
		return NULL;
	}
	toReturn = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return toReturn;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	if(InsertBefore((Node*)_itr, _element) != LIST_SUCCESS)
	{
		return NULL;
	}
	return ListItr_Prev(_itr);
}

void* ListItr_Remove(ListItr _itr)
{
	void* data;
	if(_itr == NULL || ((Node*)_itr)->m_next == NULL)
	{
		return NULL;
	}
	Remove((Node*)_itr, &data);
	return data;
}


