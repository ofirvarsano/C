#include <stdio.h>
#include "../../mu_test.h"
#include "../genericList.h"
#include "list_itr.h"

UNIT(List_Create_itr)
	int x = 6;
	ListItr iterator , iteratorEnd;
	List* list = List_Create();
	
	ASSERT_THAT(list != NULL);
	ASSERT_THAT(ListItr_Begin(NULL) == NULL);
	iterator = ListItr_Begin(list);
	ASSERT_THAT(iterator != NULL);
	
	iteratorEnd = ListItr_End(list);
	ASSERT_THAT(iteratorEnd != NULL);
	
	ASSERT_THAT(ListItr_Equals(iterator, iteratorEnd));
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	ASSERT_THAT(ListItr_Begin(list) != NULL);
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_begin_itr)
	int x = 6;
	int y = 3;
	ListItr iterator, iteratorBegin;
	List* list = List_Create();
	
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	iterator = ListItr_Begin(list);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	iteratorBegin = ListItr_Begin(list);
	ASSERT_THAT(!ListItr_Equals(iterator, iteratorBegin));
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_End_itr)
	int x = 6;
	ListItr iterator;
	List* list = List_Create();
	
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	iterator = ListItr_End(list);
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_Itr_Next)
	int x = 6;
	int y = 9;
	int z = 3;
	ListItr iterator, iteratorEnd;
	List* list = List_Create();
	
	ASSERT_THAT(ListItr_Next(NULL) == NULL);
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
	ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
	
	iterator = ListItr_Begin(list);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 3);
	iterator = ListItr_Next(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 9);
	iterator = ListItr_Next(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	iterator = ListItr_Next(iterator);
	ASSERT_THAT(ListItr_Get(iterator) == NULL);
	iterator = ListItr_Next(iterator);
	
	iteratorEnd = ListItr_End(list);
	ASSERT_THAT(ListItr_Equals(iterator, iteratorEnd));
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_Itr_Prev)
	int x = 6;
	int y = 9;
	int z = 3;
	ListItr iterator, iteratorBegin;
	List* list = List_Create();
	
	ASSERT_THAT(ListItr_Prev(NULL) == NULL);
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
	ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
	
	iteratorBegin = ListItr_Begin(list);
	iterator = ListItr_End(list);
	ASSERT_THAT(ListItr_Get(iterator) == NULL);
	
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 9);
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 3);
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 3);
	ASSERT_THAT(ListItr_Equals(iterator, iteratorBegin));
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_Itr_Set)
	int x = 6;
	int y = 9;
	ListItr iterator;
	List* list = List_Create();
	iterator = ListItr_Begin(list);
	
	ASSERT_THAT(ListItr_Set(NULL, NULL) == NULL);
	ASSERT_THAT( ListItr_Set(iterator,&x) == NULL);
	ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
	iterator = ListItr_Prev(iterator);
	ASSERT_THAT( (int*)ListItr_Set(iterator,&y) == &x);
	ASSERT_THAT(ListItr_Set(iterator, NULL) == NULL);
	List_Destroy(&list,NULL);
END_UNIT

UNIT(ListItr_Insert_Before)
	int x = 6;
	int y = 9;
	ListItr iterator;
	List* list = List_Create();
	
	ASSERT_THAT( ListItr_InsertBefore(NULL, &x) == NULL);
	iterator = ListItr_Begin(list);
	ASSERT_THAT( ListItr_InsertBefore(iterator, NULL) == NULL);
	iterator = ListItr_InsertBefore(iterator, &x);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	iterator = ListItr_InsertBefore(iterator, &y);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 9);
	iterator = ListItr_Next(iterator);
	ASSERT_THAT(*(int*)ListItr_Get(iterator) == 6);
	List_Destroy(&list,NULL);
END_UNIT

UNIT(List_Itr_Remove)
	int x = 6;
	int y = 10;
	ListItr iterator;
	List* list = List_Create();
	
	ASSERT_THAT( ListItr_Remove(NULL) == NULL);
	iterator = ListItr_Begin(list);
	ASSERT_THAT( ListItr_Remove(iterator) == NULL);
	iterator = ListItr_InsertBefore(iterator, &y);
	iterator = ListItr_InsertBefore(iterator, &x);
	ASSERT_THAT( (int*)ListItr_Remove(iterator) == &x);
	iterator = ListItr_Begin(list);
	ASSERT_THAT((int*)ListItr_Get(iterator) == &y);
	List_Destroy(&list,NULL);
END_UNIT

UNIT(end_to_end)
	int x = 6;
	int y = 10;
	int z = 3;
	int w = 44;
	ListItr iterator = NULL;
	ListItr iterator2 = NULL;
	ListItr iterator3 = NULL;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
    iterator = ListItr_Begin(list);
    ASSERT_THAT( iterator != NULL);
    iterator2 = ListItr_End(list);
    
    iterator2 = ListItr_Prev(iterator2);
    iterator2 = ListItr_Prev(iterator2);
    ASSERT_THAT( iterator == iterator2);
    ASSERT_THAT(ListItr_Equals(iterator, iterator2));
    
    ASSERT_THAT(*(int*)ListItr_Get(iterator) == 10);
    ASSERT_THAT(*(int*)ListItr_Set(iterator, &z) == 10);
    ASSERT_THAT(*(int*)ListItr_Get(iterator) == 3);
    
    iterator = ListItr_InsertBefore(iterator, &w);
    ASSERT_THAT(*(int*)ListItr_Get(iterator) == 44);
    
    ASSERT_THAT(*(int*)ListItr_Remove(iterator) == 44);
    ASSERT_THAT((int*)ListItr_Get(iterator2) == &z);
    
    iterator3 = ListItr_Next(iterator2);
    ASSERT_THAT(*(int*)ListItr_Remove(iterator2) == 3);
    
    iterator2 = ListItr_Next(iterator3);
    ASSERT_THAT(*(int*)ListItr_Remove(iterator3) == 6);
    ASSERT_THAT(ListItr_Remove(iterator2) == NULL);
    
    iterator = ListItr_Begin(list);
    ASSERT_THAT(ListItr_Get(iterator) == NULL);
    
    iterator = ListItr_InsertBefore(iterator, &w);
    ASSERT_THAT((int*)ListItr_Get(iterator) == &w);
    List_Destroy(&list,NULL);
END_UNIT


TEST_SUITE(Test List Iterator)
	TEST(List_Create_itr)
	TEST(List_begin_itr)
	TEST(List_End_itr)
	TEST(List_Itr_Next)
	TEST(List_Itr_Prev)
	TEST(List_Itr_Set)
	TEST(ListItr_Insert_Before)
	TEST(List_Itr_Remove)
	TEST(end_to_end)
END_SUITE

