#include <stdio.h>
#include "../mu_test.h"
#include "genericList.h"
#include "list_functions.h"
#include "listIterator/list_itr.h"

int lessList(void* _a, void* _b)
{
	return *(int*)_a < *(int*)_b;
}

static void printList(List* list)
{
	ListItr itr, itrEnd;
	itr = ListItr_Begin(list);
    itrEnd = ListItr_End(list);
    while( itr != itrEnd)
    {
    	printf("%d\n", *(int*)ListItr_Get(itr));
    	itr = ListItr_Next(itr);
    }
    printf("\n");
}

UNIT(List_sort)
	int x = 5, y = 6, z = 2, w = 0, q = 10, t = 25;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&q) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&t) == LIST_SUCCESS);

	printList(list);
    ListItr_Sort( ListItr_Begin(list), ListItr_End(list), lessList);
	printf("After Sort:\n");
	printList(list);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_splice)
	ListItr itr, itrEnd;
	int x = 5, y = 6, z = 2, w = 0, q = 10, t = 25;
	List* list = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&w) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&q) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&t) == LIST_SUCCESS);
    itr = ListItr_Begin(list);
    itrEnd = ListItr_End(list);
    itrEnd = ListItr_Prev(itrEnd);
    printList(list);
	ListItr_Splice( itrEnd, itr, ListItr_Next(ListItr_Next(itr)) );
	printf("After Splice:\n");
    printList(list);
    List_Destroy(&list,NULL);
END_UNIT

UNIT(List_merge)
	ListItr itr1, itr2, itrEnd1, itrEnd2, itrDest;
	int x = 1, y = 2, z = 3;
	int w = 5, q = 10, t = 25;
	List* list = List_Create();
	List* list2 = List_Create();
	List* listDest = List_Create();
    ASSERT_THAT(list != NULL);
    ASSERT_THAT( List_PushHead(list,&z) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&y) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list,&x) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list2,&t) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list2,&q) == LIST_SUCCESS);
    ASSERT_THAT( List_PushHead(list2,&w) == LIST_SUCCESS);
    itr1 = ListItr_Begin(list);
    itrEnd1 = ListItr_End(list);
    
    itr2 = ListItr_Next(ListItr_Begin(list2));
    itrEnd2 = ListItr_End(list2);
    printList(list);
    printList(list2);
    itrDest = ListItr_Begin(listDest);
    
    ListItr_Merge(itrDest, itr1, itrEnd1, itr2, itrEnd2, lessList);
	printf("After Merge:\n");
    printList(listDest);
    printList(list);
    printList(list2);
    List_Destroy(&list,NULL);
    List_Destroy(&list2,NULL);
    List_Destroy(&listDest,NULL);
END_UNIT

TEST_SUITE(Test List Iterator)
	TEST(List_sort)
	TEST(List_splice)
	TEST(List_merge)
END_SUITE
