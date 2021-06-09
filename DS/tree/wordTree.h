#ifndef _WORD_TREE_H_
#define _WORD_TREE_H_

typedef struct Node Node;
typedef struct Tree Tree;

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}TreeTraverse;

typedef enum
{
ERR_OK =0,
ERR_NOT_INITIALIZED,
ERR_UNDERFLOW,
ERR_OVERFLOW,
ERR_ALLOCATION_FAIL,
ERR_ALREADY_EXIST
} ADTErr;

/* Description:
function creates a new tree and set up its values
input- void
output- returns a pointer to the new tree
errors- no errors - return NULL if not succeed
complixity- O(1) */
Tree* TreeCreate();

/* Description:
destroys tree recursivly and free all its memory
input- pointer to a list
output- non
errors- non
complixity- O(n) */
void TreeDestroy(Tree* _tree);

/* Description:
insert a value to the right position in the tree,
inserts to root if not exists
input- pointer to tree, int data to insert
output- ADTErr error
errors- ERR_NOT_INITIALIZED if tree is NULL
ERR_ALLOCATION_FAIL if a new Node cannot be allocate
ERR_OK if succeed
complixity- O(n) */
ADTErr TreeInsert(Tree* _tree,char* _word);

/* Description:
checks if a given value exists in the tree
input- pointer to tree, int data to search
output- int - FOUND or NOT_FOUND
if tree is NULL returns NOT_FOUND
errors- non
complixity- O(n) */
int TreeIsDataFound(Tree* _tree,char* _word);

/* Description:
prints tree recursivly by pre order/in order/post order
input- pointer to tree, TreeTraverse
output- non
errors- non
complixity- O(n) */
void TreePrint(Tree* _tree,TreeTraverse _traverseMode);

#endif

