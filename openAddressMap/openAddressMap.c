#include "HashMap.h"
#include <string.h>
#include <stdlib.h>

#define MAGIC	48934537
#define PERCENT 1.3

typedef struct
{
	const void* m_key;
	void* m_value;
} Pair;

struct HashMap
{
	int m_magic;
	size_t m_capacity;
	size_t m_originalCapacity;
	int m_maxRange;
	HashFunction m_hash;
	EqualityFunction m_isEqual;
	size_t m_nElements;
	size_t m_collisions;
	Pair* m_pairs;
};

struct FindAndKey
{
	EqualityFunction m_isEqualOfUser;
	const void* m_key;
};

static size_t FindNextPrime(size_t _num);
static int isPrime(size_t _num);

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
	map->m_capacity = (size_t)((double)_capacity * PERCENT);
	if (!isPrime(map->m_capacity))
	{
		map->m_capacity = FindNextPrime(map->m_capacity);
	}
	map->m_hash = _hashFunc;
	map->m_isEqual = _keysEqualFunc;
	map->m_nElements = 0;
	map->m_collisions = 0;
	map->m_maxRange = 0;
	
	map->m_pairs = (Pair*)calloc(map->m_capacity, sizeof(Pair));
	if (map->m_pairs == NULL)
	{
		free(map);
		return NULL;
	}
	map->m_magic = MAGIC;
	return map;
}

static int isPrime(size_t _num)
{
	size_t i;
	for (i = 2; i * i <= _num; ++i)
	{
		if(_num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
static size_t FindNextPrime(size_t _num)
{
	while (!isPrime(_num))
	{
		++_num;
	}
	return _num;
}

void HashMap_Destroy(HashMap** _map, DestroyFunction _keyDestroy, DestroyFunction _valDestroy)
{
	int i;
	Pair data;
	if (_map == NULL || *_map == NULL || (*_map)->m_magic != MAGIC)
	{
		return;
	}
	for (i = 0; i < (*_map)->m_capacity; ++i)
	{
		data = (*_map)->m_pairs[i];
		if(_keyDestroy)
		{
			if (data.m_key != NULL)
			{
				_keyDestroy((void*)data.m_key);
			}
		}
		if(_valDestroy)
		{
			if (data.m_key != NULL)
			{
				_keyDestroy((void*)data.m_value);
			}
		}
	}
	free((*_map)->m_pairs);
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
	if (_map->m_nElements == _map->m_originalCapacity)
	{
		return MAP_ALLOCATION_ERROR;
	}
	return MAP_SUCCESS;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, void* _value)
{
	size_t hashNum;
	Map_Result result;
	size_t index;
	int emptyIndex = -1;
	int max = 0;
	
	result = CheckNull(_map, _key, _value);
	if (result != MAP_SUCCESS)
	{
		return result;
	}
	
	result = HashMap_Find(_map, _key, (void*)&emptyIndex);
	if (result != MAP_KEY_NOT_FOUND_ERROR)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	hashNum = _map->m_hash(_key) % _map->m_capacity;
	if (_map->m_pairs[hashNum].m_key != NULL)
	{
		++_map->m_collisions;
		if (emptyIndex != -1)
		{
			_map->m_pairs[emptyIndex].m_key = _key;
			_map->m_pairs[emptyIndex].m_value = _value;
			++_map->m_nElements;
			return MAP_SUCCESS;
		}
		index = hashNum;
		while (_map->m_pairs[index].m_key != NULL)
		{
			index = (index + 1) % _map->m_capacity;
			++max;
		}
	}
	_map->m_pairs[index].m_key = _key;
	_map->m_pairs[index].m_value = _value;
	++_map->m_nElements;
	if (max > _map->m_maxRange)
	{
		_map->m_maxRange = max;
	}
	return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
	size_t index;
	int max = 0;
	int foundDeleted = 0;
	int* deleted = malloc(sizeof(int));
	*deleted = 1;
	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = _map->m_hash(_key) % _map->m_capacity;
	if(_map->m_pairs[index].m_key == NULL)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	while (max <= _map->m_maxRange)
	{
		if (_map->m_isEqual(_key, _map->m_pairs[index].m_key))
		{
			return MAP_SUCCESS;
		}
		if (_map->m_isEqual((void*)deleted, _map->m_pairs[index].m_key && !foundDeleted)
		{
			foundDeleted = 1;
			(int)(**_pValue) = (int)index;
		}
		++max;
		++index;
	}
	return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMap_Size(const HashMap* _map)
{
	return (_map == NULL) ? 0 : _map->m_nElements;
}









