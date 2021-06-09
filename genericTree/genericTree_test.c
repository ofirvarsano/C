#include "bin_tree.h"
#include "../mu_test.h"
#include <stdlib.h>
#include <stdio.h>

int LessTreeComp(void* _left, void* _right)
{
	return *(int*)_left < *(int*)_right;
}

int Print(void* _element, void* _context)
{
	printf("%d ",*(int*)_element);
	return 1;
}

void PrintTree(BSTree* _tree)
{
	BSTree_ForEach(_tree, BSTREE_TRAVERSAL_INORDER, Print, NULL);
}

BSTree* createAndFillTree()
{
	int i;
	int size;
	BSTree* tree;
	int arr[] = {10,20,8,12,6,4,5,14,25,21,30};
	size = sizeof(arr)/sizeof(arr[0]);
	tree = BSTree_Create(LessTreeComp);
	for( i = 0; i < size; ++i)
	{
		BSTree_Insert(tree, &arr[i]);
	}
	PrintTree(tree);
	return tree;
}

UNIT(Tree_Create_ok)
	BSTree* tree = BSTree_Create(LessTreeComp);
	ASSERT_THAT( BSTree_Create(NULL) == NULL);
	ASSERT_THAT( tree != NULL);
	BSTree_Destroy(&tree,NULL);
	BSTree_Destroy(&tree,NULL);
	BSTree_Destroy(NULL,NULL);
END_UNIT

UNIT(Tree_Create_and_fill)
	BSTree* tree = createAndFillTree();
	ASSERT_THAT( tree != NULL);

	BSTree_Destroy(NULL,NULL);
END_UNIT

TEST_SUITE(Test Tree)
	TEST(Tree_Create_ok)
	TEST(Tree_Create_and_fill)
END_SUITE
