#include "personList.h"
#include <stdio.h>
#include <stdlib.h>

Person* ListInsertHead(Person* _head ,Person* _p)
{
	if(_p)
	{
		_p->m_next = _head;
		return _p;
	}
	return _head;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
	if(_item == NULL)
	{
		return _head;
	}
	if(_head == NULL)
	{
		*_item = NULL;
		return _head;
	}
	*_item = _head;
	_head = _head->m_next;
	return _head;
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	Person* currentPerson;
	Person* prev;
	prev = _head;
	if(_p == NULL)
	{
		return _head;
	}
	if(_head)
	{
		if(_head->m_id > _key)
		{
			_p->m_next = _head;
			_head = _p;
			return _head;
		}
		if(_head->m_id == _key)
		{
			return _head;
		}
		currentPerson = _head->m_next;
		while(currentPerson != NULL)
		{
			if(currentPerson->m_id == _key)
			{
				return _head;
			}
			if(currentPerson->m_id > _key)
			{
				break;
			}
			currentPerson = currentPerson->m_next;
			prev = prev->m_next;
		}
		prev->m_next = _p;
		_p->m_next = currentPerson;
		return _head;
	}
	_p->m_next = NULL;
	return _p;
}

Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
	Person* currentPerson;
	Person* prev;
	*_p = NULL;
	
	if(_p == NULL)
	{
		return _head;
	}
	if(_head)
	{
		prev = _head;
		if(_head->m_id == _key)
		{
			*_p = _head;
			_head = _head->m_next;
			return _head;
		}
		currentPerson = _head->m_next;
		while(currentPerson != NULL)
		{
			if(currentPerson->m_id == _key)
			{
				*_p = currentPerson;
				prev->m_next = currentPerson->m_next;
				return _head;
			}
			currentPerson = currentPerson->m_next;
			prev = prev->m_next;
		}
		return _head;
	}
	return NULL;
}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if(_p == NULL)
	{
		return _head;
	}
	if(_head == NULL || _head->m_id > _key)
	{
		_p->m_next = _head;
		return _p;
	}
	if(_head->m_id == _key)
	{
		return _head;
	}
	_head->m_next = ListInsertByKeyRec(_head->m_next,_key,_p);
	return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p)
{
	if(_p == NULL)
	{
		return _head;
	}
	if(_head == NULL)
	{
		*_p = NULL;
		return NULL;
	}
	if(_head->m_id == _key)
	{
		*_p = _head;
		return _head->m_next;
	}
	_head->m_next = ListRemoveByKeyRec(_head->m_next,_key,_p);
	return _head;
}

Person* ListGetLast(Person* _head)
{
	if(_head == NULL || _head->m_next == NULL)
	{
		return _head;
	}
	return ListGetLast(_head->m_next);
}

void PrintList(Person* _head)
{
	Person* currentPerson = NULL;
	currentPerson = _head;
	while(currentPerson != NULL)
	{
		printf("name: %s id: %d age: %d\n",currentPerson->m_name,currentPerson->m_id,currentPerson->m_age);
		currentPerson = currentPerson->m_next;
	}
}




