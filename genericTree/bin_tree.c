#include "bin_tree.h"
#include <stdlib.h>
#define MAGIC		94569
#define LEFT	-1
#define RIGHT	1

typedef struct Node Node;
static Node* NodeCreate(void* _item);
static BSTreeItr BSTree_ForEach_PREORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_INORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_POSTORDER(Node* _node, ActionFunction _action, void* _context);

struct Node
{
	void* m_data;
	Node* m_left;
	Node* m_right;
	Node* m_parent;
};

struct BSTree
{
	Node m_root;
	LessComparator m_less;
	int m_magic;
};

BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* tree;
	if (_less == NULL)
	{
		return NULL;
	}
	tree = (BSTree*)calloc(1,sizeof(BSTree));
	if (tree == NULL)
	{
		return NULL;
	}
	tree->m_root.m_right = &tree->m_root;
	tree->m_less = _less;
	tree->m_magic = MAGIC;
	return tree;
}

static void recursiveDestroy(Node* _root, void (*_destroyer)(void*))
{
	if (_root == NULL)
	{
		return;
	}
	recursiveDestroy(_root->m_left, _destroyer);
	recursiveDestroy(_root->m_right, _destroyer);
	if (_destroyer)
	{
		_destroyer(_root->m_data);
	}
	free(_root);
}

void BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if (_tree && *_tree && (*_tree)->m_magic == MAGIC)
	{
		recursiveDestroy((*_tree)->m_root.m_left, _destroyer);
		
		(*_tree)->m_magic = 0;
		free(*_tree);
		*_tree = NULL;
	}
}

static BSTreeItr Insert(BSTree* _tree, Node* _parent, void* _item, LessComparator _less)
{
	Node* newNode = NodeCreate(_item);
	if(!newNode)
	{
		return (BSTreeItr) &_tree->m_root;
	}
	newNode->m_parent = _parent;

	if(_less(_item, _parent->m_data))
	{
		_parent->m_left = newNode;
	}
	else
	{
		_parent->m_right = newNode;
	}
	return (BSTreeItr) newNode;
}

static BSTreeItr Findparent(Node* _node, void* _item, LessComparator _less)
{
	if(_less(_item, _node->m_data))
	{
		if(!_node->m_left)
		{
			return (BSTreeItr)_node;
		}
		return Findparent(_node->m_left, _item, _less);
	}
	if(_less(_node->m_data, _item))
	{
		if(!_node->m_right)
		{
			return (BSTreeItr)_node;
		}
		return Findparent(_node->m_right, _item, _less);
	}
	return NULL;
}

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	Node *parent;
	if (_tree == NULL || _item == NULL)
	{
		return BSTreeItr_End(_tree);
	}
	if(_tree->m_root.m_left == NULL)
	{
		_tree->m_root.m_left = NodeCreate(_item);
		if(!(_tree->m_root.m_left))
		{
			return (BSTreeItr) &_tree->m_root;
		}

		_tree->m_root.m_left->m_parent = &_tree->m_root;

		return (BSTreeItr) _tree->m_root.m_left; 
	}
	parent = (Node*)Findparent(_tree->m_root.m_left, _item, _tree->m_less);
	if(!parent)
	{
		return (BSTreeItr) &_tree->m_root;
	}
	return Insert(_tree, parent, _item, _tree->m_less);
}

BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	Node* current = NULL;
	if(_tree == NULL)
	{
		return NULL;
	}
	current = (Node*)&_tree->m_root;
	
	while (current->m_left)
	{
		current = current->m_left;
	}
	return (BSTreeItr)current;
}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(_tree == NULL)
	{
		return NULL;
	}
	return (BSTreeItr)&_tree->m_root;
}

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return _a == _b;
}

BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* parent = NULL;
	if ( ((Node*)_it)->m_parent == NULL)
	{
		return _it;
	}
	if ( ((Node*)_it)->m_right != NULL)
	{
		_it = (BSTreeItr)((Node*)_it)->m_right;
		while ( ((Node*)_it)->m_left != NULL)
		{
			_it = (BSTreeItr)((Node*)_it)->m_left;
		}
	}
	else
	{
		parent = ((Node*)_it)->m_parent;
		while ( (Node*)_it == parent->m_right)
		{
			_it = (BSTreeItr)parent;
			parent = parent->m_parent;
		}
		if (((Node*)_it)->m_right != parent)
		{
			_it = (BSTreeItr)parent;
		}
	}
	return (BSTreeItr)_it;
}

BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* parent = NULL;
	if ( ((Node*)_it)->m_left != NULL)
	{
		_it = (BSTreeItr)((Node*)_it)->m_left;
		while ( ((Node*)_it)->m_right != NULL)
		{
			_it = (BSTreeItr)((Node*)_it)->m_right;
		}
	}
	else
	{
		parent = ((Node*)_it)->m_parent;
		while ( (Node*)_it == parent->m_left)
		{
			if (parent == parent->m_right)
			{
				return (BSTreeItr)_it;
			}
			_it = (BSTreeItr)parent;
			parent = parent->m_parent;
		}
	}
	return (BSTreeItr)_it;
}

void* BSTreeItr_Get(BSTreeItr _it)
{
	if (_it == NULL || (Node*)_it == ((Node*)_it)->m_right)
	{
		return NULL;
	}
	return ((Node*)_it)->m_data;
}

BSTreeItr BSTree_FindFirst(BSTreeItr _begin, BSTreeItr _end, PredicateFunction _predicate, void* _context)
{
	BSTreeItr current = _begin;
	if (!_predicate)
	{
		return _end;
	}
	while (current != NULL && current != _end)
	{
		if( (!_predicate( BSTreeItr_Get(current), _context)) )
		{
			return (BSTreeItr)current;
		}
		current = BSTreeItr_Next(current);
	}
	return (BSTreeItr)current;
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
		default : return NULL;
	}
}
/*
void* BSTreeItr_Remove(BSTreeItr _it)
{
	BSTreeItr next;
	void* data;
	if (_it == NULL)
	{
		return NULL;
	}
	data = ((Node*)_it)->m_data;
	if ( ((Node*)_it)->m_right && ((Node*)_it)->m_left)
	{
		next = BSTreeItr_Next(_it);
		((Node*)_it)->m_data = ((Node*)next)->m_data;
		_it = next;
	}
	
	if (((Node*)_it)->m_right)
	{
		((Node*)_it)->m_data = ((Node*)_it)->m_right->m_data;
		free(((Node*)_it)->m_right);
	}
	else if (((Node*)_it)->m_left)
	{
		((Node*)_it)->m_data = ((Node*)_it)->m_left->m_data;
		free(((Node*)_it)->m_left);
	}
	else
	{
		free(_it);
	}
	return data;
}

static BSTreeItr Next(BSTreeItr _root, TreeTraversalMode _mode)
{
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER: return BSTreeItr_Next(_root);
		break;
		case BSTREE_TRAVERSAL_INORDER: return BSTreeItr_Next(_root);
		break;
		case BSTREE_TRAVERSAL_POSTORDER: return BSTreeItr_Next(_root);
		break;
		default: return NULL;
	}
}

BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
	BSTreeItr root, end;
	if (_tree == NULL || _action == NULL)
	{
		return NULL;
	}
	root = (BSTreeItr)_tree->m_root.m_left;
	end = BSTreeItr_End(_tree);
	while (root != end)
	{
		if( (!_action(((Node*)root)->m_data, _context)))
		{
			break;
		}
		root = Next(root, _mode);
	}
	return root;
}
*/
static Node* NodeCreate(void* _item)
{
	Node* newNode = (Node*) malloc(sizeof(Node));
	if(!newNode)
	{
		return NULL;
	}

	newNode->m_data = _item;
	newNode->m_parent = NULL;
	newNode->m_left = NULL;
	newNode->m_right = NULL;

	return newNode;
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









