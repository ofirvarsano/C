#include "tree.h"
#include "treeErrors.h"
#include <stdlib.h>
#include <stdio.h>
#define MAGIC		3456
#define NOT_FOUND	0
#define FOUND		1

#define EXIST		0
#define LEFT		-1
#define RIGHT		1

typedef struct Node Node;

struct Node
{
	int m_data;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

struct Tree
{
	Node* m_root;
	int m_magic;
};

static int Maximum(int x, int y)
{
	return x > y ? x : y;
}

Tree* TreeCreate()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if(tree == NULL)
	{
		return NULL;
	}
	tree->m_root = NULL;
	tree->m_magic = MAGIC;
	return tree;
}

void recursiveDestroy(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	recursiveDestroy(_root->m_left);
	recursiveDestroy(_root->m_right);
	free(_root);
}

void TreeDestroy(Tree* _tree)
{
	if(_tree && _tree->m_magic == MAGIC)
	{
		recursiveDestroy(_tree->m_root);
		
		_tree->m_magic = 0;
		free(_tree);
	}
}

static int GetPosition(Node** _father,int _data)
{
	Node* current = *_father;
	int side = EXIST;
	while(current != NULL)
	{
		if(_data < current->m_data)
		{
			side = LEFT;
			*_father = current;
			current = current->m_left;
		}
		else if(_data > current->m_data)
		{
			side = RIGHT;
			*_father = current;
			current = current->m_right;
		}
		else
		{
			return EXIST;
		}
	}
	return side;
}

ADTErr TreeInsert(Tree* _tree,int _data)
{
	Node* newNode = NULL;

	Node* father = NULL;

	if(_tree == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	newNode = (Node*)calloc(1,sizeof(Node));
	if(newNode == NULL)
	{
		return ERR_ALLOCATION_FAIL;
	}
	newNode->m_data = _data;
	if(_tree->m_root == NULL)
	{
		_tree->m_root = newNode;
		return ERR_OK;
	}
	father = _tree->m_root;
	switch(GetPosition(&father,_data))
	{
		case EXIST: 
				free(newNode);
				return ERR_ALREADY_EXIST;
				break;
		case LEFT:
				father->m_left = newNode;
				newNode->m_father = father;
				break;
		case RIGHT:
				father->m_right = newNode;
				newNode->m_father = father;
				break;
	}
	return ERR_OK;
}

int TreeIsDataFound(Tree* _tree,int _data)
{
	if(_tree == NULL || _tree->m_root == NULL)
	{
		return NOT_FOUND;
	}
	
	if(GetPosition(&_tree->m_root,_data) == EXIST)
	{
		return FOUND;
	}
	return NOT_FOUND;
}

static void PrintPreOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	printf("%d ",_root->m_data);
	PrintPreOrder(_root->m_left);
	PrintPreOrder(_root->m_right);
}

static void PrintInOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	PrintInOrder(_root->m_left);
	printf("%d ",_root->m_data);
	PrintInOrder(_root->m_right);
}

static void PrintPostOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	PrintPostOrder(_root->m_left);
	PrintPostOrder(_root->m_right);
	printf("%d ",_root->m_data);
}

void TreePrint(Tree* _tree,TreeTraverse _traverseMode)
{
	if(_tree != NULL)
	{
		switch(_traverseMode)
		{
			case PRE_ORDER: PrintPreOrder(_tree->m_root);
			break;
			case IN_ORDER: PrintInOrder(_tree->m_root);
			break;
			case POST_ORDER: PrintPostOrder(_tree->m_root);
			break;
		}
		printf("\n");
	}
}

int RecursiveLevel(Node* _root)
{
	if(_root == NULL)
	{
		return -1;
	}
	return 1 + Maximum(RecursiveLevel(_root->m_right),RecursiveLevel(_root->m_left));
}

int CheckTreeLevel(Tree* _tree)
{
	if(_tree == NULL)
	{
		return -1;
	}
	return RecursiveLevel(_tree->m_root);
}

int RecursiveFull(Node* _root)
{
	int level,levelRight,levelLeft;
	level = RecursiveLevel(_root);
	if(level == 0)
	{
		return 1;
	}
	
	if(level > 0)
	{
		levelRight = RecursiveLevel(_root->m_right);
		levelLeft = RecursiveLevel(_root->m_left);
		if(levelRight == level - 1 && levelLeft == level - 1 && RecursiveFull(_root->m_right) && RecursiveFull(_root->m_left))
		{
			return 1;
		}
	}
	return 0;
}

int isFullTree(Tree* _tree)
{
	if(_tree == NULL)
	{
		return 1;
	}
	return RecursiveFull(_tree->m_root);
}

void RecursiveMirror(Node* _root)
{
	Node* temp = NULL;
	if(RecursiveLevel(_root) == 0)
	{
		return;
	}
	RecursiveMirror(_root->m_right);
	RecursiveMirror(_root->m_left);
	
	temp = _root->m_right;
	_root->m_right = _root->m_left;
	_root->m_left = temp;
}

void MirrorTree(Tree* _tree)
{
	if(_tree == NULL)
	{
		return;
	}
	RecursiveMirror(_tree->m_root);
}

int RecursiveSimilar(Node* _root1, Node* _root2)
{
	if(RecursiveLevel(_root1) != RecursiveLevel(_root2))
	{
		return 0;
	}
	if(RecursiveLevel(_root1) <= 0 && RecursiveLevel(_root2) <= 0)
	{
		return 1;
	}

	RecursiveSimilar(_root1->m_right,_root2->m_right);
	RecursiveSimilar(_root1->m_left,_root2->m_left);
	if(RecursiveLevel(_root1->m_right) == RecursiveLevel(_root2->m_right) && RecursiveLevel(_root1->m_left) == RecursiveLevel(_root2->m_left))
	{
		return 1;
	}
	return 0;

}

int AreSimilar(Tree* _tree1, Tree* _tree2)
{
	if(_tree1 == NULL && _tree2 == NULL)
	{
		return 1;
	}
	else if((_tree1 == NULL && _tree2 != NULL) || (_tree2 == NULL && _tree1 != NULL))
	{
		return 0;
	}
	return RecursiveSimilar(_tree1->m_root,_tree2->m_root);
}

int findDepth(Node* _root)
{
	Node* node = _root;
	int d = 0;
	while(node != NULL)
	{
		++d;
		node = node->m_left;
	}
	return d;
}

int isPerfectRec(Node* _root,int _depth, int _level)
{
	if(_root == NULL)
	{
		return 1;
	}
	if(_root->m_left == NULL && _root->m_right == NULL)
	{
		return (_depth == _level + 1);
	}
	if(_root->m_left == NULL || _root->m_right == NULL)
	{
		return 0;
	}
	return isPerfectRec(_root->m_left,_depth,_level + 1) && isPerfectRec(_root->m_right,_depth,_level + 1);
}

int IsPerfectTree(Tree* _tree)
{
	int d = findDepth(_tree->m_root);
	if(_tree == NULL)
	{
		return 1;
	}
	return isPerfectRec(_tree->m_root,d,0);
}

int isBSTRec(Node* _root,int prev)
{
	if(_root == NULL)
	{
		return 1;
	}
	if(!isBSTRec(_root->m_left,prev))
	{
		return 0;
	}  
	if(_root->m_data <= prev)
	{
		return 0;
	}
	prev = _root->m_data;
	return isBSTRec(_root->m_right,prev);
}

int isBST(Tree* _tree)
{
	if(_tree == NULL)
	{
		return 1;
	}
	return isBSTRec(_tree->m_root,-1);
}


