#include <stdio.h>
#include "genericHeap.h"
#include "../genericVector/genericVector.h"
#include "mu_test.h"

int	CompareInt(const void *_left, const void *_right)
{
	return *(int*)_left > *(int*)_right;
}

int PrintArr(void* _element, size_t _index, void* _context)
{
	int* item = _element;
	printf("%d, ", *item);
	return 1;
}

UNIT(Heap_Build_creation_legal_values)
	int x = 5;
	int y = 10;
	int z = 7;
	int w = 18;
	int t = 11;
	int r = 13;
	Heap* heap;
	Vector* vec = Vector_Create(2,2);
	Vector_Append(vec, &x);
	Vector_Append(vec, &y);
	Vector_Append(vec, &z);
	Vector_Append(vec, &w);
	Vector_Append(vec, &r);
	heap = Heap_Build(vec,CompareInt);
	ASSERT_THAT( heap != NULL);
	Vector_ForEach(vec, PrintArr, NULL);
	printf("\n");
	ASSERT_THAT( Heap_Insert(heap,&t) == HEAP_SUCCESS);
	ASSERT_THAT( *(int*)Heap_Peek(heap) == 18);
	Vector_ForEach(vec, PrintArr, NULL);
	printf("\n");
	ASSERT_THAT( *(int*)Heap_Extract(heap) == 18);
	Vector_ForEach(vec, PrintArr, NULL);
	printf("\n");
	ASSERT_THAT( Heap_Size(heap) == 5);
	Vector_Destroy(&vec,NULL);
	ASSERT_THAT( Heap_Insert(heap,&t) == HEAP_NOT_INITIALIZED);
	vec = Heap_Destroy(&heap);
	Vector_Destroy(&vec,NULL);
END_UNIT

TEST_SUITE(test HEAP)
	IGNORE_TEST(Heap_Build_NULL_args)
	IGNORE_TEST(Heap_Build_creation_zero_length_vector)
	IGNORE_TEST(Heap_Build_creation_1000_length_vector)
	TEST(Heap_Build_creation_legal_values)
	IGNORE_TEST(Heap_Build_check_root_correction) /* use several different vectors */
	IGNORE_TEST(Heap_Size_NULL_args)
	IGNORE_TEST(Heap_Size_empty)
	IGNORE_TEST(Heap_Size_ok)
	IGNORE_TEST(Heap_insert_NULL_args)
	IGNORE_TEST(Heap_insert_to_built_heap)
	IGNORE_TEST(Heap_insert_to_empty_heap)
	IGNORE_TEST(Heap_insert_many_items) /* size 1000 with random values */
	IGNORE_TEST(Heap_insert_check_realloc) /* fail and success fixed vector */
	IGNORE_TEST(Heap_Peek_NULL_args)
	IGNORE_TEST(Heap_Peek_ok)
	IGNORE_TEST(Heap_Peek_empty_heap)	
	IGNORE_TEST(Heap_Extract_NULL_args)
	IGNORE_TEST(Heap_Extract_one_element)
	IGNORE_TEST(Heap_Extract_empty_heap)
	IGNORE_TEST(Heap_Size_diff_sizes)
	IGNORE_TEST(Heap_Size_end_to_end) /* all test in one. check by peek and size */
	IGNORE_TEST(Heap_Size_end_to_end_different_type)

END_SUITE
