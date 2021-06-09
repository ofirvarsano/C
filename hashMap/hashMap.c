#include "HashMap.h"
#include <string.h>
#include <stdlib.h>
#include "../genericList/genericList.h"
#include "../genericList/list_functions.h"
#include "../genericList/listIterator/list_itr.h"

#define MAGIC	48934537
#define PERCENT(x)	((x) + ((x)/6))


struct HashMap
{
	int m_magic;
	size_t m_capacity;
	HashFunction m_hash;
	EqualityFunction m_isEqual;
	size_t m_nElements;
	List** m_listArr;
};

typedef struct
{
	const void* m_key;
	void* m_value;
} Pair;

struct FindAndKey
{
	EqualityFunction m_isEqualOfUser;
	const void* m_key;
};

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* map;
	if (_hashFunc == NULL || _keysEqualFunc == NULL || _capacity < 1)
	{
		return NULL;
	}
	map = (HashMap*)malloc(sizeof(HashMap));
	if (map == NULL)
	{
		return NULL;
	}
	map->m_capacity = PERCENT(_capacity);
	map->m_hash = _hashFunc;
	map->m_isEqual = _keysEqualFunc;
	map->m_nElements = 0;
	
	map->m_listArr = (List**)calloc(map->m_capacity, sizeof(List*));
	if (map->m_listArr == NULL)
	{
		free(map);
		return NULL;
	}
	map->m_magic = MAGIC;
	return map;
}

static void DestroyList(List* _list, DestroyFunction _keyDestroy, DestroyFunction _valDestroy)
{
	ListItr it = ListItr_Begin(_list);
	ListItr end = ListItr_End(_list);
	Pair* data;
	while (it != end)
	{
		data = (Pair*)ListItr_Get(it);
		if(_keyDestroy)
		{
			_keyDestroy((void*)data->m_key);
		}
		if(_valDestroy)
		{
			_valDestroy((void*)data->m_value);
		}
		free(data);
		it = ListItr_Next(it);
	}
	List_Destroy(&_list, NULL);
}

void HashMap_Destroy(HashMap** _map, DestroyFunction _keyDestroy, DestroyFunction _valDestroy)
{
	int i;
	if (_map == NULL || *_map == NULL || (*_map)->m_magic != MAGIC)
	{
		return;
	}
	for (i = 0; i < (*_map)->m_capacity; ++i)
	{
		if((*_map)->m_listArr[i] != NULL)
		{
			DestroyList((*_map)->m_listArr[i], _keyDestroy, _valDestroy);
		}
	}
	free((*_map)->m_listArr);
	(*_map)->m_magic = 0;
	free(*_map);
	*_map = NULL;
}

static Map_Result CheckNull(HashMap* _map, const void* _key, void* _value)
{
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if (_value == NULL)
	{
		return MAP_VALUE_NULL_ERROR;
	}
	return MAP_SUCCESS;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, void* _value)
{
	size_t hashNum;
	Pair* pair;
	void* val;
	Map_Result result;
	ListItr end;
	
	result = CheckNull(_map, _key, _value);
	if (result != MAP_SUCCESS)
	{
		return result;
	}

	result = HashMap_Find(_map, _key, &val);
	if (result != MAP_KEY_NOT_FOUND_ERROR)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}

	hashNum = _map->m_hash(_key) % _map->m_capacity;
	if (_map->m_listArr[hashNum] == NULL)
	{
		_map->m_listArr[hashNum] = List_Create();
		if (_map->m_listArr[hashNum] == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
	}

	pair = (Pair*)malloc(sizeof(Pair));
	if (pair == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	pair->m_key = _key;
	pair->m_value = _value;

	end = ListItr_End(_map->m_listArr[hashNum]);
	ListItr_InsertBefore(end, pair);
	++_map->m_nElements;

	return MAP_SUCCESS;
}

int HashIsEqual(void* _listValue, void* _context)
{
	struct FindAndKey* findInfo = (struct FindAndKey*)_context;
	Pair* current = (Pair*)_listValue;
	return findInfo->m_isEqualOfUser(current->m_key, findInfo->m_key);
}

static ListItr isFound(const HashMap* _map, const void* _key, size_t hashNum)
{
	ListItr begin, end;
	struct FindAndKey context;
	
	if (_map->m_listArr[hashNum] == NULL)
	{
		return NULL;
	}
	
	context.m_isEqualOfUser = _map->m_isEqual;
	context.m_key = _key;

	begin = ListItr_Begin(_map->m_listArr[hashNum]);
	end = ListItr_End(_map->m_listArr[hashNum]);
	return ListItr_FindFirst(begin, end, HashIsEqual, &context);
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, const void** _pKey, void** _pValue)
{
	size_t hashNum;
	ListItr itr, end;
	Pair* pair;
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (_searchKey == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	hashNum = _map->m_hash(_searchKey) % _map->m_capacity;
	end = ListItr_End(_map->m_listArr[hashNum]);
	
	itr = isFound(_map, _searchKey, hashNum);
	if (ListItr_Equals(itr, end))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	pair = (Pair*)ListItr_Remove(itr);
	--_map->m_nElements;
	*_pValue = pair->m_value;
	*_pKey = pair->m_key;
	free(pair);
	return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
	ListItr itr, end;
	size_t hashNum;
	
	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	hashNum = _map->m_hash(_key) % _map->m_capacity;
	if(_map->m_listArr[hashNum])
	{
		itr = isFound(_map, _key, hashNum);
		end = ListItr_End(_map->m_listArr[hashNum]);
		if (itr != end)
		{
			*_pValue = ((Pair*)ListItr_Get(itr))->m_value;
			return MAP_SUCCESS;
		}
	}
	return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMap_Size(const HashMap* _map)
{
	if (_map == NULL)
	{
		return 0;
	}
	return _map->m_nElements;
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	int i;
	Pair* pair;
	ListItr begin, end;
	size_t count = 0;
	
	if (_map == NULL || _action == NULL)
	{
		return count;
	}
	for (i = 0; i < _map->m_capacity; ++i)
	{
		if(_map->m_listArr[i])
		{
			begin = ListItr_Begin(_map->m_listArr[i]);
			end = ListItr_End(_map->m_listArr[i]);
			while (begin != end)
			{
				++count;
				pair = (Pair*)ListItr_Get(begin);
				if (!_action(pair->m_key, pair->m_value, _context))
				{
					return count;
				}
				begin = ListItr_Next(begin);
			}
		}
	}
	return count;
}

int	Add(const void* _key, void* _value, void* _context)
{
	HashMap_Insert((HashMap*)_context, _key, _value);
	return 1;
}

static void swapMap(HashMap *_map1, HashMap *_map2)
{
	HashMap temp;
	memcpy(&temp, _map1, sizeof(HashMap));
	memcpy(_map1, _map2, sizeof(HashMap));
	memcpy(_map2, &temp, sizeof(HashMap));
}
 
Map_Result HashMap_Rehash(HashMap *_map, size_t newCapacity)
{
	HashMap* newMap;
	
	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	newMap = HashMap_Create(newCapacity, _map->m_hash, _map->m_isEqual);
	if (newMap == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	HashMap_ForEach(_map, Add, newMap);
	swapMap(_map, newMap);
	/* DestroyAll(&newMap, NULL, NULL, 0); */
	HashMap_Destroy(&newMap, NULL, NULL);

	return MAP_SUCCESS;
}





