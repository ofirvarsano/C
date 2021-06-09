#include <stdio.h>
#include "../mu_test.h"
#include "HashMap.h"

int	PrintPair(const void* _key, void* _value, void* _context)
{
	printf("key:\t%d\tvalue:\t%d\n", *(int*)_key, *(int*)_value);
	return 1;
}

size_t hash(const void* _key)
{
	return (size_t)(*(int*)_key);
}

int EqualInt(const void* _firstKey, const void* _secondKey)
{
	return *(int*)_firstKey == *(int*)_secondKey;
}
/*
HashMap* FillMap(int arr[], int size)
{
	int i = 0;
	HashMap* map = HashMap_Create(10,hash,EqualInt);
	while (i < size)
	{
		HashMap_Insert(map, &arr[i], &arr[i+1]);
		i += 2;
	}
	return map;
}
*/
UNIT(hashCreate)
	HashMap* map;
	ASSERT_THAT(HashMap_Create(0,NULL,NULL) == NULL);
	ASSERT_THAT(HashMap_Create(5,NULL,EqualInt) == NULL);
	ASSERT_THAT(HashMap_Create(1,hash,NULL) == NULL);
	map = HashMap_Create(50,hash,EqualInt);
	ASSERT_THAT(map != NULL);
	HashMap_Destroy(&map,NULL,NULL);
	ASSERT_THAT(map == NULL);
END_UNIT

UNIT(hashDestroy)
	HashMap* map = HashMap_Create(10,hash,EqualInt);
	ASSERT_THAT(map != NULL);
	HashMap_Destroy(&map,NULL,NULL);
	HashMap_Destroy(&map,NULL,NULL);
END_UNIT
/*
UNIT(hashInsert)
	HashMap* map;
	int arr[] = {111,3,234,15,45,1,77,0,111,6};
	map = FillMap(arr, 7);
	ASSERT_THAT(HashMap_Insert(map, &arr[8], &arr[9]) == MAP_KEY_DUPLICATE_ERROR);
	HashMap_ForEach(map, PrintPair, NULL);
	HashMap_Destroy(&map,NULL,NULL);
END_UNIT

UNIT(hashRemove)
	int arr[] = {111,3,234,15,45,1,77,0};
	int* key, *value, *numP;
	int num = 92;
	HashMap* map = NULL;
	numP = &num;
	ASSERT_THAT(HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value) == MAP_UNINITIALIZED_ERROR);
	map = FillMap(arr, 7);
	ASSERT_THAT(map != NULL);
	
	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	ASSERT_THAT(HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value) == MAP_KEY_NOT_FOUND_ERROR);
	ASSERT_THAT(HashMap_Remove(map, &numP, (const void**)&key, (void**)&value) == MAP_KEY_NOT_FOUND_ERROR);
	ASSERT_THAT(*(int*)key == 234);
	ASSERT_THAT(*(int*)value == 15);
	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	HashMap_Destroy(&map,NULL,NULL);
END_UNIT

UNIT(hashFind)
	int arr[] = {111,3,234,15,45,1,77,0};
	int* key, *value;
	HashMap* map = NULL;
	
	map = FillMap(arr, 7);
	ASSERT_THAT(map != NULL);
	
	ASSERT_THAT(HashMap_Find(map, &arr[2], (void**)&value) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(map, &arr[2], (void**)&value) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(map, &arr[2], (void**)&value) == MAP_KEY_NOT_FOUND_ERROR);
	ASSERT_THAT(HashMap_Find(map, &arr[1], (void**)&value) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	ASSERT_THAT(HashMap_Rehash(map,17) == MAP_SUCCESS);
	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	HashMap_Destroy(&map,NULL,NULL);
END_UNIT

UNIT(hashRehash)
	int arr[] = {111,3,234,15,45,1,77,0};
	HashMap* map = NULL;
	
	map = FillMap(arr, 7);
	ASSERT_THAT(map != NULL);

	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	ASSERT_THAT(HashMap_Rehash(map,17) == MAP_SUCCESS);
	HashMap_ForEach(map, PrintPair, NULL);
	printf("\n");
	HashMap_Destroy(&map,NULL,NULL);
END_UNIT
*/
TEST_SUITE(Test Hash)
	TEST(hashCreate)
	TEST(hashDestroy)
	/*IGNORE_TEST(hashInsert)
	IGNORE_TEST(hashRemove)
	IGNORE_TEST(hashFind)
	IGNORE_TEST(hashRehash)*/
END_SUITE





