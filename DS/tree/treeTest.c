#include "tree.h"
#include "treeErrors.h"
#include <stdio.h>

void test1()
{
	Tree* tree = TreeCreate();
	if(tree == NULL)
	{
		printf("TreeCreate() FAIL\n");
	}
	else
	{
		printf("TreeCreate() PASS\n");
		TreeDestroy(tree);
	}
}

/* TreeDestroy tests */

void test2()
{
	Tree* tree = TreeCreate();
	TreeDestroy(tree);
	printf("TreeDestroy() PASS\n");
}

void test3()
{
	Tree* tree = NULL;
	TreeDestroy(tree);
	printf("TreeDestroy() PASS\n");
}

void test4()
{
	Tree* tree = TreeCreate();
	TreeDestroy(tree);
	TreeDestroy(tree);
	printf("TreeDestroy() PASS\n");
}

void test5()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,8);
	TreeInsert(tree,6);
	TreeDestroy(tree);
	TreePrint(tree,IN_ORDER);
	printf("TreeDestroy() PASS\n");
}

/* TreeInsert tests */

void test6()
{
	Tree* tree = NULL;
	if(TreeInsert(tree,10) == ERR_NOT_INITIALIZED)
	{
		printf("TreeInsert(NULL,10) PASS\n");
	}
	else
	{
		printf("TreeInsert(NULL,10) FAIL\n");
	}
}

void test7()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	if(TreeInsert(tree,10) == ERR_ALREADY_EXIST)
	{
		printf("TreeInsert(tree,10) PASS\n");
	}
	else
	{
		printf("TreeInsert(tree,10) FAIL\n");
	}
	TreeDestroy(tree);
}

void test8()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,11);
	if(TreeIsDataFound(tree,10) == 1)
	{
		if(TreeIsDataFound(tree,11) == 1)
		{
			printf("TreeInsert PASS\n");
		}
		else
		{
			printf("TreeInsert FAIL\n");
		}
	}
	else
	{
		printf("TreeInsert FAIL\n");
	}
	TreeDestroy(tree);
}

void test9()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,8);
	TreeInsert(tree,6);
	TreeInsert(tree,9);
	TreeInsert(tree,8);
	TreeInsert(tree,12);
	TreePrint(tree,IN_ORDER);
	printf("TreeInsert PASS\n");
	TreeDestroy(tree);
}

void test10()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,3);
	TreeInsert(tree,3);
	TreeInsert(tree,3);
	TreeInsert(tree,6);
	TreeInsert(tree,9);
	TreeInsert(tree,1);
	TreeInsert(tree,12);
	TreePrint(tree,IN_ORDER);
	printf("TreeInsert PASS\n");
	TreeDestroy(tree);
}

/* TreeIsDataFound tests */

void test11()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,9);
	TreeInsert(tree,6);
	TreeInsert(tree,10);
	TreeInsert(tree,11);
	if(TreeIsDataFound(tree,10) == 1)
	{
		if(TreeIsDataFound(tree,11) == 1)
		{
			printf("TreeIsDataFound PASS\n");
		}
		else
		{
			printf("TreeIsDataFound FAIL\n");
		}
	}
	else
	{
		printf("TreeIsDataFound FAIL\n");
	}
	TreeDestroy(tree);
}

void test12()
{
	Tree* tree = TreeCreate();
	if(TreeIsDataFound(tree,10) == 0)
	{
		printf("TreeIsDataFound PASS\n");
	}
	else
	{
		printf("TreeIsDataFound FAIL\n");
	}
	TreeDestroy(tree);
}

void test13()
{
	Tree* tree = NULL;
	if(TreeIsDataFound(tree,10) == 0)
	{
		printf("TreeIsDataFound PASS\n");
	}
	else
	{
		printf("TreeIsDataFound FAIL\n");
	}
}

void test14()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,8);
	if(TreeIsDataFound(tree,10) == 0)
	{
		printf("TreeIsDataFound PASS\n");
	}
	else
	{
		printf("TreeIsDataFound FAIL\n");
	}
	TreeDestroy(tree);
}

void test15()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,8);
	TreeInsert(tree,12);
	TreeInsert(tree,6);
	TreeInsert(tree,9);
	TreeInsert(tree,7);
	TreeInsert(tree,11);
	TreeInsert(tree,13);
	TreePrint(tree,PRE_ORDER);
	TreePrint(tree,IN_ORDER);
	TreePrint(tree,POST_ORDER);
	printf("TreePrintPASS\n");
	TreeDestroy(tree);
}

void test16()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,9);
	TreeInsert(tree,11);
	TreeInsert(tree,12);
	printf("Tree Level: %d\n",CheckTreeLevel(tree));
	TreeDestroy(tree);
}

void test17()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,12);
	TreeInsert(tree,13);
	TreeInsert(tree,11);
	printf("is full: %d\n",isFullTree(tree));
	TreeDestroy(tree);
}

void test18()
{
	Tree* tree1 = TreeCreate();
	Tree* tree2 = TreeCreate();
	TreeInsert(tree1,10);
	TreeInsert(tree2,12);
	
	TreeInsert(tree1,11);
	TreeInsert(tree2,10);
	
	TreeInsert(tree1,9);
	TreeInsert(tree2,13);
	printf("are similar: %d\n",AreSimilar(tree1,tree2));
	TreeDestroy(tree1);
	TreeDestroy(tree2);
}

void test19()
{
	Tree* tree = TreeCreate();
	TreeInsert(tree,10);
	TreeInsert(tree,11);
	TreeInsert(tree,12);
	printf("is BST: %d\n",isBST(tree));
	TreeDestroy(tree);
}

int main()
{
	/* TreeCreate tests */
	test1();
	/* TreeDestroy tests */
	test2();
	test3();
	test4();
	test5();
	/* TreeInsert tests */
	test6();
	test7();
	test8();
	test9();
	test10();
	/* TreeIsDataFound tests */
	test11();
	test12();
	test13();
	test14();
	/* TreePrint tests */
	test15();
	test16();
	test17();
	test18();
	test19();
	
	return 0;
}

