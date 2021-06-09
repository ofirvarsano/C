#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int m_data;
	Node* m_next;
}Node;

Node* flip(Node* _node)
{
	Node* temp;
	if(_node == NULL || _node->m_next == NULL)
	{
		return _node;
	}
	
	temp = flip(_node->m_next);
	_node->m_next->m_next = _node;
	_node->m_next = NULL;
	
	return temp;
	
}
