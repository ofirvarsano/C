#ifndef __LIST_STRUCTS_H__
#define __LIST_STRUCTS_H__

typedef enum List_Result{
	LIST_SUCCESS = 0,
	LIST_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	LIST_NULL_ELEMENT_ERROR,
	LIST_UNDERFLOW_ERROR
	/* Add more as needed by your implementation */
	
}List_Result;

typedef struct Node Node;
List_Result InsertBefore(Node* _t, void* _item);
List_Result Remove(Node* _toRemove, void** _pItem);

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	int m_magic;
};

#endif
