#include "genericVector.h"
#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

int PrintArr(void* _element, size_t _index, void* _context)
{
	int* item = _element;
	/**(int*)_context += *item;*/
	printf("%d, ", *item);
	return 1;
}

int IsNotEqualInt(void* _element, size_t _index, void* _context)
{
	return *(int*)_element != *(int*)_context;
}

size_t Find(Vector* _vec, void* _element , VectorElementAction _isNotEqual)
{
	return Vector_ForEach(_vec, _isNotEqual, _element);
}

/*
size_t FindInVec(Vector* _vec, void* _element , int (*_isEqual)(void* _ element, void* _context))
{
	return Vector_ForEach(_vec, _isNotEqual, _element);
}
*/

int SumInt(void* _element, size_t _index, void* _context)
{
	int* item = _element;
	if(NULL == _element || NULL == _context)
	{
		return 0;
	}
	*(int*)_context += *item;
	return 1;
}

UNIT(generic_vector_create)
	ASSERT_THAT( Vector_Create(2,2) != NULL);
	ASSERT_THAT( Vector_Create(2,0) != NULL);
	ASSERT_THAT( Vector_Create(0,2) != NULL);
	ASSERT_THAT( Vector_Create(0,0) == NULL);
END_UNIT

UNIT(generic_vector_destroy)
	Vector* vec = Vector_Create(2,2);
	Vector_Destroy(&vec,NULL);
	ASSERT_THAT( vec == NULL);
END_UNIT

/* TODO ASSERT_THAT for all lines */
UNIT(generic_vector_double_destroy)
	Vector* vec = Vector_Create(2,2);
	Vector_Destroy(&vec,NULL);
	Vector_Destroy(&vec,NULL);
	ASSERT_THAT( vec == NULL);
END_UNIT

UNIT(generic_vector_for_each_print)
	int a = 1;
	int b = 2;
	int c = 3;
	Vector* vec = Vector_Create(6,2);
	Vector_Append(vec, &a);
	Vector_Append(vec, &b);
	Vector_Append(vec, &c);
	ASSERT_THAT( Vector_ForEach(vec, PrintArr, NULL) == 3);
	printf("\n");
	Vector_Destroy(&vec,NULL);
END_UNIT

int CheckArrItem(void* _element, size_t _index, void* _context)
{
	int* arr = _context;
	return arr[_index] == *(int*)_element;
}
/*
UNIT(generic_vector_for_each)
	Vector* vec;
	size_t i;
	int arr[] = {2,3,4,88};
	vec = Vector_Create(5,1);
	for(i = 0; i < ARR_SIZE(arr); ++i)
	{
		ASSERT_THAT(Vector_Append(vec, arr + i) == VECTOR_SUCCESS);
	}
	i = Find(vec, 4);
	ASSERT_THAT(i == 2);
	Vector_Destroy(&vec,NULL);
END_UNIT
*/
UNIT(generic_vector_for_each_find)
	Vector* vec;
	size_t i;
	int x = 4;
	int arr[] = {2,3,4,88};
	vec = Vector_Create(5,1);
	for(i = 0; i < ARR_SIZE(arr); ++i)
	{
		ASSERT_THAT(Vector_Append(vec, arr + i) == VECTOR_SUCCESS);
	}
	i = Find(vec, (void*)&x, IsNotEqualInt);

	ASSERT_THAT(i == 2);
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(generic_vector_for_each_sum)
	int a = 1;
	int b = 2;
	int c = 3;
	int sum = 0;
	Vector* vec = Vector_Create(1,2);
	Vector_Append(vec, &a);
	Vector_Append(vec, &b);
	Vector_Append(vec, &c);
	ASSERT_THAT(Vector_ForEach(vec, SumInt, (void*)&sum) == 3);
	ASSERT_THAT(sum == 6);
	ASSERT_THAT(Vector_ForEach(vec, SumInt, NULL) == 0);
	
	Vector_Destroy(&vec,NULL);
END_UNIT


TEST_SUITE(generic vector test)
	TEST(generic_vector_create)
	TEST(generic_vector_destroy)
	TEST(generic_vector_double_destroy)
	TEST(generic_vector_for_each_print)
	TEST(generic_vector_for_each_sum)
	/*TEST(generic_vector_for_each)*/
	TEST(generic_vector_for_each_find)
END_SUITE


