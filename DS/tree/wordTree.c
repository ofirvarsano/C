#include "wordTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAGIC		3456
#define NOT_FOUND	0
#define FOUND		1
#define SIZE		50
#define EXIST		0
#define LEFT		-1
#define RIGHT		1

struct Node
{
	char m_word[SIZE];
	int m_count;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

struct Tree
{
	Node* m_root;
	int m_magic;
};

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
int GetPosition(Node** _father,char* _word)
{
	Node* current = *_father;
	int side = EXIST;
	while(current != NULL)
	{
		if(strcmp(_word,current->m_word) < 0)
		{
			side = LEFT;
			*_father = current;
			current = current->m_left;
		}
		else if(strcmp(_word,current->m_word) > 0)
		{
			side = RIGHT;
			*_father = current;
			current = current->m_right;
		}
		else if(strcmp(_word,current->m_word) == 0)
		{
			*_father = current;
			return EXIST;
		}
	}
	return side;
}

ADTErr TreeInsert(Tree* _tree,char* _word)
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
	strcpy(newNode->m_word,_word);
	newNode->m_count = 1;
	if(_tree->m_root == NULL)
	{
		newNode->m_father = NULL;
		_tree->m_root = newNode;
		return ERR_OK;
	}
	father = _tree->m_root;
	switch(GetPosition(&father,_word))
	{
		case EXIST: 
				free(newNode);
				father->m_count = father->m_count + 1;
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

int TreeIsDataFound(Tree* _tree,char* _word)
{
	Node* temp = NULL;
	if(_tree == NULL)
	{
		return NOT_FOUND;
	}
	if(_tree->m_root == NULL)
	{
		return NOT_FOUND;
	}
	temp = _tree->m_root;
	if(GetPosition(&temp,_word) == EXIST)
	{
		return FOUND;
	}
	return NOT_FOUND;
}

void PrintPreOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	printf("%s\t%d\n",_root->m_word,_root->m_count);
	PrintPreOrder(_root->m_left);
	PrintPreOrder(_root->m_right);
}

void PrintInOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	PrintInOrder(_root->m_left);
	printf("%s\t%d\n",_root->m_word,_root->m_count);
	PrintInOrder(_root->m_right);
}

void PrintPostOrder(Node* _root)
{
	if(_root == NULL)
	{
		return;
	}
	PrintPostOrder(_root->m_left);
	PrintPostOrder(_root->m_right);
	printf("%s\t%d\n",_root->m_word,_root->m_count);
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
	}
}

