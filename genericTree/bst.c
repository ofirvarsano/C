#include <stdlib.h>
#include "/home/arie/work/advanceC/Includes/bst.h"

#define MAGIC 	897496584

typedef struct Node Node;
struct Node
{
	void*	m_data;
	Node*	m_left;
	Node*	m_right;
	Node*	m_father;
};

struct  BSTree
{
	int m_magic;
	LessComparator m_less;
	Node m_root;
};


static void DestroyNodesAndDataRec(Node* _root, void (*_destroyer)(void*));
static Node* NodeCreate(void* _item);
static Node* FindTheFatherOfDataToInsert(Node* _node, void* _item, LessComparator _less);
static BSTreeItr TreeInsertNodeWithFather(BSTree* _tree, Node* _father, void* _item, LessComparator _less);
static int IsLeaf(Node* _node);
static void* RemoveLeaf(Node* _node);
static int HasOneChild(Node* _node);
static void* RemoveNodeWithOneChild(Node* _node);
static void SwapValues(Node* _n1, Node* _n2);
static BSTreeItr BSTree_ForEach_PREORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_INORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_POSTORDER(Node* _node, ActionFunction _action, void* _context);


BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* tree = NULL;

	if(!_less)
	{
		return NULL;
	}

 	tree = (BSTree*) malloc(sizeof(BSTree));
	if(!tree)
	{
		return NULL;
	}

	tree->m_magic = MAGIC;
	tree->m_less = _less;

	tree->m_root.m_data = NULL;
	tree->m_root.m_father = NULL;
	tree->m_root.m_left = NULL;
	tree->m_root.m_right = &tree->m_root;

	return tree;
}

void  BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if(!_tree  ||  !*_tree  ||  (*_tree)->m_magic != MAGIC)
	{
		return;
	}

	if((*_tree)->m_root.m_left)
	{
		DestroyNodesAndDataRec((*_tree)->m_root.m_left, _destroyer);
	}

	free(*_tree);
	*_tree = NULL;
}

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	Node* father = NULL;

	if(!_tree)
	{
		return NULL;
	}

	if(!_item)
	{
		return (BSTreeItr) &_tree->m_root;
	}

	if(NULL == _tree->m_root.m_left)
	{
		_tree->m_root.m_left = NodeCreate(_item);
		if(!(_tree->m_root.m_left))
		{
			return (BSTreeItr) &_tree->m_root;
		}

		_tree->m_root.m_left->m_father = &_tree->m_root;

		return (BSTreeItr) _tree->m_root.m_left; 
	}

	father = FindTheFatherOfDataToInsert(_tree->m_root.m_left, _item, _tree->m_less);
	if(!father) /* The value already exist */
	{
		return (BSTreeItr) &_tree->m_root;
	}

	return TreeInsertNodeWithFather(_tree, father, _item, _tree->m_less);
}

BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	BSTreeItr itr;

	if(!_tree)
	{
		return NULL;
	}

	itr = (BSTreeItr) &_tree->m_root;

	while((BSTreeItr) ((Node*) itr)->m_left != NULL)
	{
		itr = (BSTreeItr) ((Node*) itr)->m_left;
	}

	return itr;
}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	return !_tree ? NULL : (BSTreeItr) &_tree->m_root;
}

BSTreeItr BSTree_FindFirst(BSTreeItr _begin, BSTreeItr _end, PredicateFunction _predicate, void* _context)
{
	BSTreeItr result;

	if(_begin == NULL  ||  _end == NULL  ||   _begin == _end  ||  !_predicate)
	{
		return _end;
	}

	result = BSTree_FindFirst((BSTreeItr) ((Node*) _begin)->m_left, _end, _predicate, _context);
	if(result != _end)
	{
		return result;
	}

	if(_predicate(((Node*) _begin)->m_data, _context) != 0)
	{
		return _begin;
	}

	return BSTree_FindFirst((BSTreeItr) ((Node*) _begin)->m_right, _end, _predicate, _context);
}

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return _a == _b;
}

BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* node = NULL;

	if(!_it)
	{
		return NULL;
	}

	node = (Node*) _it;

	if(node->m_right) /* The next is one right and left at the end */
	{
		node = node->m_right;
		while(node->m_left)
		{
			node = node->m_left;
		}

		return (BSTreeItr) node;
	}

	while(node->m_father->m_right == node)
	{
		node = node->m_father;
	}

	return (BSTreeItr) node->m_father; /* Will return the root if the value is already the maximum */
}

BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* node = NULL;

	if(!_it)
	{
		return NULL;
	}

	node = (Node*) _it;

	if(node->m_left) /* The prev is one left and right at the end */
	{
		node = node->m_left;
		while(node->m_right)
		{
			node = node->m_right;
		}

		return (BSTreeItr) node;
	}

	while(node->m_father->m_left == node)
	{
		node = node->m_father;
	}

	return (BSTreeItr) node->m_father; /* Will return the root if the value is already the minimum */
}

void* BSTreeItr_Remove(BSTreeItr _it)
{
	BSTreeItr nextItr;
	if(!_it)
	{
		return NULL;
	}

	if(IsLeaf((Node*) _it))
	{
		return RemoveLeaf((Node*) _it);
	}

	if(HasOneChild((Node*) _it))
	{
		return RemoveNodeWithOneChild((Node*) _it);
	}

	nextItr = BSTreeItr_Next(_it);

	SwapValues((Node*) _it, (Node*) nextItr);

	return RemoveNodeWithOneChild((Node*) nextItr);
}

void* BSTreeItr_Get(BSTreeItr _it)
{
	if(!_it  ||  ((Node*) _it)->m_right == (Node*) _it)
	{
		return NULL;
	}

	return ((Node*) _it)->m_data;
}

BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
	BSTreeItr result; 

	if (!_tree  ||  !_action)
	{
		return NULL;
	}

	if (!_tree->m_root.m_left)
	{
		return (BSTreeItr) &_tree->m_root;
	}

	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
			result =  BSTree_ForEach_PREORDER(_tree->m_root.m_left, _action, _context);
			return (result == NULL) ? (BSTreeItr) &_tree->m_root : result;

		case BSTREE_TRAVERSAL_INORDER:
			result = BSTree_ForEach_INORDER(_tree->m_root.m_left, _action, _context);
			return (result == NULL) ? (BSTreeItr) &_tree->m_root : result;

		case BSTREE_TRAVERSAL_POSTORDER:
			result = BSTree_ForEach_POSTORDER(_tree->m_root.m_left, _action, _context);
			return (result == NULL) ? (BSTreeItr) &_tree->m_root : result;

		/*case BSTREE_TRAVERSAL_DEPTH_FIRST:
			result = BSTree_ForEach_DFS(_tree->m_root.m_left, _action, _context);
			return (result == NULL) ? (BSTreeItr) &_tree->m_root : result;

		case BSTREE_TRAVERSAL_BREADTH_FIRST:
			result = BSTree_ForEach_BFS(_tree->m_root.m_left, _action, _context);
			return (result == NULL) ? (BSTreeItr) &_tree->m_root : result;*/

		default : 
			return NULL;
	}
}





		/* *************************************** HELP FUNCTIONS ****************************************** */



static void DestroyNodesAndDataRec(Node* _root, void (*_destroyer)(void*))
{
	if(!_root)
	{
		return;
	}

	DestroyNodesAndDataRec(_root->m_left, _destroyer);
	DestroyNodesAndDataRec(_root->m_right, _destroyer);

	_root->m_left = NULL;
	_root->m_right = NULL;
	_root->m_father = NULL;

	if(_destroyer)
	{
		_destroyer(_root->m_data);
	}

	free(_root);
}

static Node* NodeCreate(void* _item)
{
	Node* newNode = (Node*) malloc(sizeof(Node));
	if(!newNode)
	{
		return NULL;
	}

	newNode->m_data = _item;
	newNode->m_father = NULL;
	newNode->m_left = NULL;
	newNode->m_right = NULL;

	return newNode;
}

static Node* FindTheFatherOfDataToInsert(Node* _node, void* _item, LessComparator _less)
{
	if(_less(_item, _node->m_data))
	{
		if(!_node->m_left)
		{
			return _node;
		}

		return FindTheFatherOfDataToInsert(_node->m_left, _item, _less);
	}

	if(_less(_node->m_data, _item))
	{
		if(!_node->m_right)
		{
			return _node;
		}

		return FindTheFatherOfDataToInsert(_node->m_right, _item, _less);
	}

	return NULL;
}

static BSTreeItr TreeInsertNodeWithFather(BSTree* _tree, Node* _father, void* _item, LessComparator _less)
{
	Node* newNode = NodeCreate(_item);
	if(!newNode)
	{
		return (BSTreeItr) &_tree->m_root;
	}

	newNode->m_father = _father;

	if(_less(_item, _father->m_data))
	{
		_father->m_left = newNode;
	}

	else
	{
		_father->m_right = newNode;
	}

	return (BSTreeItr) newNode;
}

static int IsLeaf(Node* _node)
{
	if(_node->m_left == NULL  &&  _node->m_right == NULL)
	{
		return 1;
	}

	return 0;
}

static void* RemoveLeaf(Node* _node)
{
	void* erasedData = _node->m_data;

	_node->m_data = NULL;
	_node->m_left = NULL;
	_node->m_right = NULL;

	if(_node->m_father->m_left == _node)
	{
		_node->m_father->m_left = NULL;
	}

	else if(_node->m_father->m_right == _node)
	{
		_node->m_father->m_right = NULL;
	}

	_node->m_father = NULL;

	free(_node);

	return erasedData;
}

static void* RemoveNodeWithOneChild(Node* _node)
{
	if(_node->m_left)
	{
		if(_node->m_father->m_left == _node)
		{
			_node->m_father->m_left = _node->m_left;
		}

		else
		{
			_node->m_father->m_right = _node->m_left;
		}
	}	

	else if(_node->m_right)
	{
		if(_node->m_father->m_left == _node)
		{
			_node->m_father->m_left = _node->m_right;
		}

		else
		{
			_node->m_father->m_right = _node->m_right;
		}
	}

	return RemoveLeaf(_node);
}

static int HasOneChild(Node* _node)
{
	if((_node->m_left && !_node->m_right)  || (!_node->m_left && _node->m_right))
	{
		return 1;
	}

	return 0;
}

static void SwapValues(Node* _n1, Node* _n2)
{
	void* temp = _n1->m_data;

	_n1->m_data = _n2->m_data;

	_n2->m_data = temp;
}

static BSTreeItr BSTree_ForEach_PREORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr result;

	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr) _node;
	}

	if(_node->m_left)
	{
		result = BSTree_ForEach_PREORDER(_node->m_left, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	if(_node->m_right)
	{
		result = BSTree_ForEach_PREORDER(_node->m_right, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	return NULL;
}

static BSTreeItr BSTree_ForEach_INORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr result;

	if(_node->m_left)
	{
		result = BSTree_ForEach_PREORDER(_node->m_left, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr) _node;
	}

	if(_node->m_right)
	{
		result = BSTree_ForEach_PREORDER(_node->m_right, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	return NULL;
}

static BSTreeItr BSTree_ForEach_POSTORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr result;

	if(_node->m_left)
	{
		result = BSTree_ForEach_PREORDER(_node->m_left, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	if(_node->m_right)
	{
		result = BSTree_ForEach_PREORDER(_node->m_right, _action, _context);
		if(result != NULL)
		{
			return result;
		}
	}

	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr) _node;
	}

	return NULL;
}
