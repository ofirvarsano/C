#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>
#include "listErrors.h"

typedef struct List List;

/* Description:
function creates a new list and set up its values
input- void
output- returns a pointer to the new list
errors- no errors - return NULL if not succeed
complixity- O(1) */
List* ListCreate(void);

/* Description:
destroys list and free all its memory
input- pointer to a list
output- non
errors- non
complixity- O(n) */
void ListDestroy(List* _list);

/* Description:
push a value to the head of the list
input- pointer to list, int data to push
output- ADTErr error
errors- ERR_NOT_INITIALIZED if list is NULL
ERR_ALLOCATION_FAIL if a new Node cannot be allocate
ERR_OK if succeed
complixity- O(1) */
ADTErr ListPushHead(List* _list, int _data);

/* Description:
push a value to the tail of the list
input- pointer to list, int data to push
output- ADTErr error
errors- ERR_NOT_INITIALIZED if list is NULL
ERR_ALLOCATION_FAIL if a new Node cannot be allocate
ERR_OK if succeed
complixity- O(1) */
ADTErr ListPushTail(List* _list, int _data);

/* Description:
pops a value from the top of the list to item-int pointer
input- pointer to list, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if list or item is NULL
ERR_UNDERFLOW if list is empty
ERR_OK if succeed
complixity- O(1) */
ADTErr ListPopHead(List* _list, int* _data);

/* Description:
pops a value from the tail of the list to item-int pointer
input- pointer to list, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if list or item is NULL
ERR_UNDERFLOW if list is empty
ERR_OK if succeed
complixity- O(1) */
ADTErr ListPopTail(List* _list, int* _data);

/* Description:
returns number of items in the list. 0 if empty or NULL
input- pointer to list
output- non
complixity- O(n) */
size_t ListCountItems(List* _list);

/* Description:
checks list is empty
input- pointer to list
output- int - 1 if list ia empty or NULL, 0 if not empty
errors- non
complixity- O(1) */
int ListIsEmpty(List* _list);

/* ListPrint is only for debug */

/* Description:
prints list items
input- pointer to list
output- non
errors- non
complixity- O(n) */
void ListPrint(List* _list);

#endif
