#include <stdio.h>
#include "../mu_test.h"
#include "genericList.h"

UNIT(List_Create_ok)
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    List_Destroy(&list,NULL);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_All_PushHead)
	int x = 6;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,NULL) == LIST_NULL_ELEMENT_ERROR);
    ASSERT_THAT( List_PushHead(NULL,NULL) == LIST_UNINITIALIZED_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PophHead_ok)
	int x = 6;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PopHead(list, NULL) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PopHead(NULL, (void**)&y) == LIST_UNINITIALIZED_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PophHead_several_items)
	int x = 6, z = 7, w = 3;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 3);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 7);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    ASSERT_THAT( List_PushHead(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 3);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_All_PushTail)
	int x = 6;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushTail(list,NULL) == LIST_NULL_ELEMENT_ERROR);
    ASSERT_THAT( List_PushTail(NULL,NULL) == LIST_UNINITIALIZED_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PophTail_ok)
	int x = 6;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PopTail(list, NULL) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT( List_PopTail(NULL, (void**)&y) == LIST_UNINITIALIZED_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PushHead_PopTail)
	int x = 6;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PushHead_PopTail_NULL_element)
	int x = 6;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PopTail(list, NULL) == LIST_NULL_ELEMENT_ERROR);

    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_PophTail_several_items)
	int x = 6, z = 7, w = 3;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushTail(list,&z) == LIST_SUCCESS);
    ASSERT_THAT( List_PushTail(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 3);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 7);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 6);
    ASSERT_THAT( List_PushTail(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT( *(int*)y == 3);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_Size_NULL)
    ASSERT_THAT(List_Size(NULL) == 0);
END_UNIT

UNIT(List_Size_ok)
	int x = 6;
	int* y;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT(List_Size(list) == 0);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT(List_Size(list) == 1);
    ASSERT_THAT( List_PushTail(list,&x) == LIST_SUCCESS);
    ASSERT_THAT(List_Size(list) == 2);
    ASSERT_THAT( List_PopHead(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT(List_Size(list) == 1);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_SUCCESS);
    ASSERT_THAT(List_Size(list) == 0);
    ASSERT_THAT( List_PopTail(list, (void**)&y) == LIST_UNDERFLOW_ERROR);
    ASSERT_THAT(List_Size(list) == 0);
    List_Destroy(&list,NULL);
END_UNIT


TEST_SUITE(Test List)
	TEST(List_Create_ok)
    TEST(List_All_PushHead)
    TEST(List_PophHead_ok)
    TEST(List_PophHead_several_items)
    TEST(List_All_PushTail)
    TEST(List_PophTail_ok)
    TEST(List_PushHead_PopTail)
    TEST(List_PophTail_several_items)
    TEST(List_PushHead_PopTail_NULL_element)
    TEST(List_Size_NULL)
    TEST(List_Size_ok)
END_SUITE




