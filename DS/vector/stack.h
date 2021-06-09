#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>

typedef struct Stack Stack;

/* Description:
function creates a new stack
input- receives size for the initial stack, and blockSize for resizing when necessary. (blockSize cannot be 0)
output- returns a pointer to the new stack
errors- no errors - return NULL if not succeed
complixity- O(1) */
Stack* StackCreate(size_t _size, size_t _blockSize);


/* Description:
destroys stack and free all its memory
input- pointer to a stack
output- non
errors- non
complixity- O(1) */
void StackDestroy(Stack* _stack);


/* Description:
push a value to the top of the stack
input- pointer to stack, int item to push
output- ADTErr error
errors- ERR_NOT_INITIALIZED if stack is NULL
ERR_REALLOCATION_FAILED if theres no room and cannot allocate a new address
ERR_OK if succeed
complixity- O(1) */
ADTErr StackPush(Stack* _stack, int _item);


/* Description:
pops a value from the top of the stack to item-int pointer
input- pointer to stack, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if stack or item is NULL
ERR_UNDERFLOW if stack is empty
ERR_OK if succeed
complixity- O(1) */
ADTErr StackPop(Stack* _stack, int* _item);


/* Description:
looks at the value at top of the stack
input- pointer to stack, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if stack or item is NULL
ERR_UNDERFLOW if stack is empty
ERR_OK if succeed
complixity- O(1) */
ADTErr StackTop(Stack* _stack, int* _item);


/* Description:
returns 1 if stack is empty or NULL, 0 if not
input- pointer to stack
output- int
errors- non
complixity- O(1) */
int StackIsEmpty(Stack* _stack);

/* Unit-Test functions */
/* Description:
prints stack
input- pointer to stack
output- non
errors- non
complixity- O(n) */
void StackPrint(Stack* _stack);

#endif

