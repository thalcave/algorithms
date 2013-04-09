#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

struct Node
{
	unsigned val;
	Node* next;

	Node(unsigned v): val(v), next(0) {}
};

#endif
