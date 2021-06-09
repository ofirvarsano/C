#ifndef _TREE_H_
#define _TREE_H_
#include "treeErrors.h"

typedef struct Tree Tree;

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}TreeTraverse;

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
ERR_ALREADY_EXIST if duplicate
ERR_OK if succeed
complixity- O(log(n)) */
ADTErr TreeInsert(Tree* _tree,int _data);

/* Description:
checks if a given value exists in the tree
input- pointer to tree, int data to search
output- int - FOUND or NOT_FOUND
if tree is NULL returns NOT_FOUND
errors- non
complixity- O(log(n)) */
int TreeIsDataFound(Tree* _tree,int _data);

/* Description:
prints tree recursivly by pre order/in order/post order
input- pointer to tree, TreeTraverse
output- non
errors- non
complixity- O(n) */
void TreePrint(Tree* _tree,TreeTraverse _traverseMode);


int CheckTreeLevel(Tree* _tree);
int isFullTree(Tree* _tree);
void MirrorTree(Tree* _tree);
int AreSimilar(Tree* _tree1, Tree* _tree2);
int IsPerfectTree(Tree* _tree);
int isBST(Tree* _tree);

#endif

