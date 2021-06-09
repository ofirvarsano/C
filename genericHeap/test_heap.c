#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "genericHeap.h"
#include "../genericVector/genericVector.h"

typedef struct Person 
{
    int     m_id;         /* Primary Key */
    char    m_name[128];
    int     m_age;
    struct Person* m_next;
} Person;


static void InsertArrayToVec(int* _arr, Vector* _vec, int _size );
static void IntGetRandomArray(int *_arr, int _n);


int compareInt(const void* _a, const void* _b )
{
	return (*(int*)_a > *(int*)_b);
}

int comparePerson(const void* _a, const void* _b )
{
	return ((Person*)_a)->m_age > ((Person*)_b)->m_age;
}

int PrintArr(void* _element, size_t _index, void* _context)
{
	int* item = _element;
	printf("%d, ", *item);
	return 1;
}

UNIT(Heap_Build_Null_args)

	ASSERT_THAT(Heap_Build(NULL, compareInt) == NULL);
	ASSERT_THAT(Heap_Build(NULL, NULL) == NULL );		
END_UNIT


UNIT(Heap_Build_creation_zero_length_vector)
	Vector* vec = NULL;
	ASSERT_THAT((vec = Vector_Create(0 , 2)) != NULL);
	ASSERT_THAT(Heap_Build(vec, compareInt) != NULL);	
END_UNIT

UNIT(Heap_Build_creation_legal_values)
	Vector* vec = NULL;
	ASSERT_THAT((vec = Vector_Create(5 , 2)) != NULL);
	ASSERT_THAT(Heap_Build(vec, compareInt) != NULL);	
END_UNIT


UNIT(Heap_Build_check_root_correctness)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	void* value = NULL;
	Heap* heap = NULL;
	
	vec = Vector_Create(5 , 2);
	InsertArrayToVec(arr, vec, 4);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT( *(int*)value == 4);
	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT

UNIT(Heap_Build_check_root_correctness_Person)
	Person p[5]= {{300, "Itay", 5, NULL}, {400, "sivan", 2, NULL}, {500, "Maya", 10, NULL} , {600, "Stas", 10, NULL}, {700, "Guy", 3, NULL}};
	Vector* vec = NULL;
	void* value = NULL ;
	Heap* heap = NULL;
	
	vec = Vector_Create(5,2);
	ASSERT_THAT(Vector_Append(vec , (p)) == VECTOR_SUCCESS);
	ASSERT_THAT(Vector_Append(vec , (p+1)) == VECTOR_SUCCESS);
	ASSERT_THAT(Vector_Append(vec , (p+2)) == VECTOR_SUCCESS);

	ASSERT_THAT((heap = Heap_Build(vec, comparePerson)) != NULL);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT( ((Person*)value)->m_age == 10);
	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT

UNIT(Heap_Size_Null_args)
	ASSERT_THAT(Heap_Size(NULL) == 0);
END_UNIT


UNIT(Heap_Size_empty)
	Vector* vec = NULL;
	Vector *tempVec = NULL;
	Heap* heap = NULL;
	
	ASSERT_THAT((vec = Vector_Create(5 , 2)) != NULL);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Size(heap) == 0);
	ASSERT_THAT((tempVec = Heap_Destroy(&heap)) == vec) ;
	Vector_Destroy(&vec, NULL);	
	
END_UNIT



UNIT(Heap_Size_ok)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	Heap* heap = NULL;	
	
	vec = Vector_Create(5 , 2);
	InsertArrayToVec(arr, vec, 4);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Size(heap) == 4);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT


UNIT(Heap_Peek_Null_args)
	ASSERT_THAT(Heap_Peek(NULL) == 0);
END_UNIT

UNIT(Heap_Peek_empty_heap)
	Vector* vec = NULL;
	Vector *tempVec = NULL;
	Heap* heap = NULL;
	
	ASSERT_THAT((vec = Vector_Create(5 , 2)) != NULL);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Peek(heap) == 0);
	ASSERT_THAT((tempVec = Heap_Destroy(&heap)) == vec) ;
	Vector_Destroy(&vec, NULL);	
	
END_UNIT



UNIT(Heap_Peek_ok)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	void* value = NULL;
	Heap* heap = NULL;	
	
	vec = Vector_Create(5 , 2);
	InsertArrayToVec(arr, vec, 4);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT(Heap_Peek(heap) == value);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT


UNIT(Heap_insert_Null_args)
	void* element= NULL;
	Heap* heap = NULL;
	Vector* vec = NULL;
	
	ASSERT_THAT((vec = Vector_Create(5 , 2)) != NULL);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Insert(NULL, element) == HEAP_NOT_INITIALIZED);
	Heap_Destroy(&heap);	
END_UNIT



UNIT(Heap_insert_to_empty_heap)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	Heap* heap = NULL;	
	void* value = NULL;
	
	vec = Vector_Create(5 , 2);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Insert(heap, arr) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 1);
	ASSERT_THAT(Heap_Insert(heap, arr+1) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 2);
	ASSERT_THAT(Heap_Insert(heap, arr+2) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 3);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT( *(int*)value == 3);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT


UNIT(Heap_insert_check_fixed_vector)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	Heap* heap = NULL;	
	
	vec = Vector_Create(1 , 0);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Insert(heap, arr) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 1);
	ASSERT_THAT(Heap_Insert(heap, arr+1) == HEAP_REALLOCATION_FAILED);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT


UNIT(Heap_insert_check_realloc_many_items)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	Heap* heap = NULL;	
	void* value = NULL;
	
	vec = Vector_Create(1 , 1);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Insert(heap, arr) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 1);
	ASSERT_THAT(Heap_Insert(heap, arr+1) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 2);
	ASSERT_THAT(Heap_Insert(heap, arr+2) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 3);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT( *(int*)value == 3);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT


UNIT(Heap_Extract_Null_args)
	ASSERT_THAT(Heap_Extract(NULL) == NULL);
END_UNIT
	

UNIT(Heap_Extract_element)
	Vector* vec = NULL;
	int arr[5] = {1,2,3,4};
	Heap* heap = NULL;	
	void* value = NULL;
	
	vec = Vector_Create(5 , 1);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Heap_Insert(heap, arr) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 1);
	ASSERT_THAT(Heap_Insert(heap, arr+1) == HEAP_SUCCESS);
	ASSERT_THAT(Heap_Size(heap) == 2);
	ASSERT_THAT((value = Heap_Extract(heap)) != NULL);
	ASSERT_THAT(Heap_Size(heap) == 1);
	ASSERT_THAT( *(int*)value == 2);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT( *(int*)value == 1);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT
	
UNIT(Heap_Extract_empty)
	Vector* vec = NULL;
	Heap* heap = NULL;	
	
	vec = Vector_Create(5 , 1);
	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT((Heap_Extract(heap)) == NULL);

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT
	
	
	
UNIT(Heap_end_to_end)
	Vector* vec = NULL;
	int arr[100];
	Heap* heap = NULL;	
	void* value = NULL;
	int i;
	vec = Vector_Create(80 , 2);
	IntGetRandomArray(arr, 100);
	InsertArrayToVec(arr, vec, 80);

	ASSERT_THAT((heap = Heap_Build(vec, compareInt)) != NULL);
	ASSERT_THAT(Vector_Get(vec, 0, &value) == VECTOR_SUCCESS);
	ASSERT_THAT((Heap_Peek(heap) == value));
	
	for (i=0; i < 20 ; ++i )
	{
		ASSERT_THAT(Heap_Insert(heap, arr + (80 + i)) == HEAP_SUCCESS);

		ASSERT_THAT(Heap_Size(heap) == (81 + i));
	}
	for (i=100; i > 0 ; --i )
	{
		ASSERT_THAT((value = Heap_Extract(heap)) != NULL);
		ASSERT_THAT(Heap_Size(heap) == (i - 1));
	}

	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec, NULL);
	
END_UNIT

TEST_SUITE(Test Heap)
	TEST(Heap_Build_Null_args)
	TEST(Heap_Build_creation_zero_length_vector)
	TEST(Heap_Build_creation_legal_values)
	TEST(Heap_Build_check_root_correctness)
	TEST(Heap_Build_check_root_correctness_Person)
	TEST(Heap_Size_Null_args)
	TEST(Heap_Size_empty)
	TEST(Heap_Size_ok)
	TEST(Heap_Peek_Null_args)
	TEST(Heap_Peek_ok)
	TEST(Heap_Peek_empty_heap)	
	TEST(Heap_insert_Null_args)
	IGNORE_TEST(Heap_insert_to_built_heap)
	TEST(Heap_insert_to_empty_heap)
	TEST(Heap_insert_check_fixed_vector)
	TEST(Heap_insert_check_realloc_many_items)
	TEST(Heap_Extract_Null_args)
	TEST(Heap_Extract_element)

    /* Check inserts, extracts and again by peek, and size */
	TEST(Heap_end_to_end)

END_SUITE


static void InsertArrayToVec( int* _arr, Vector* _vec, int _size )
{
	int i=0;
	for(i=0; i<_size ; ++i)
	{
		Vector_Append(_vec, _arr+i);
	}
}

static void IntGetRandomArray(int *_arr, int _n)
{
	int i;

	for (i=0; i<_n; ++i)
	{
		_arr[i]= rand()%(_n);
	}
}
