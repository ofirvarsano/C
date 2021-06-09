#include "list_functions.h"
#include "listIterator/list_itr.h"
#include <stdlib.h>

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr current = _begin;
	if(!_predicate)
	{
		return _end;
	}
	while( current != NULL && current != _end && ListItr_Next(current) != NULL)
	{
		if( (*_predicate)( ListItr_Get(current), _context) )
		{
			return (ListItr)current;
		}
		current = ListItr_Next(current);
	}
	return (ListItr)current;
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t count = 0;
	ListItr current = _begin;
	if(!_predicate)
	{
		return count;
	}
	while( current != NULL && current != _end && ListItr_Next(current) != NULL)
	{
		if( (*_predicate)( ListItr_Get(current), _context) )
		{
			++count;
		}
		current = ListItr_Next(current);
	}
	return count;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	ListItr current = _begin;
	if(!_action)
	{
		return _end;
	}
	while( current != NULL && current != _end && ListItr_Next(current) != NULL)
	{
		if( !(*_action)( ListItr_Get(current), _context) )
		{
			return (ListItr)current;
		}
		current = ListItr_Next(current);
	}
	return (ListItr)current;
}

void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	void* temp;
	int swapped;
	ListItr current;
	ListItr left = _end;
	
	if(!_less || _begin == NULL)
	{
		return;
	}
	do
	{
		swapped = 0;
		current = _begin;
		while( ListItr_Next(current) != left && ListItr_Next(current) != NULL)
		{
			if( (*_less)( ListItr_Get(current), ListItr_Get(ListItr_Next(current)) ) )
			{
				temp = ListItr_Get(current);
				ListItr_Set(current, ListItr_Get(ListItr_Next(current)));
				ListItr_Set( ListItr_Next(current), temp);
				swapped = 1;
			}
			current = ListItr_Next(current);
		}
		left = current;
	}while(swapped);
}

ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	while(_begin != _end && ListItr_Next(_begin) != NULL)
	{
		ListItr_InsertBefore(_dest, ListItr_Get(_begin));
		_begin = ListItr_Next(_begin);
		
		ListItr_Remove(ListItr_Prev(_begin));
	}
	return _dest;
}

ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	if( !_less)
	{
		return _destBegin;
	}
	if( (*_less)( ListItr_Get(_firstBegin), ListItr_Get(ListItr_Next(_secondBegin))) )
	{
		ListItr_Splice(_destBegin, _firstBegin, _firstEnd);
		ListItr_Splice(_destBegin, _secondBegin, _secondEnd);
	}
	else
	{
		ListItr_Splice(_destBegin, _secondBegin, _secondEnd);
		ListItr_Splice(_destBegin, _firstBegin, _firstEnd);
	}
	return _destBegin;
}	














