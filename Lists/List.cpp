#include "List.hpp"
#include <iostream>

List::List()
: head(0)
{
}

List::~List()
{
	Node* cnode = head;
	while (cnode)
	{
		Node* prev = cnode;
		cnode = cnode->next;
		delete prev;
	}
}

void
List::addElem(unsigned v)
{
	if (!head)
	{
		head = new Node(v);
		return;
	}
	
	Node* cnode = head;
	while (cnode->next)
	{
		cnode = cnode->next;
	}

	cnode->next = new Node(v);
}

void
List::print() const
{
	std::cout<<"List: ";
	Node* cnode = head;
	while (cnode)
	{
		std::cout<<"["<<cnode->val<<"] ";
		cnode = cnode->next;
	}
	std::cout<<"\n";	
}

bool
List::delElem(unsigned v)
{
	if (!head)
	{
		//empty list
		return false;
	}

	//case #1: elem to delete is head
	if (head->val == v)
	{
		Node* temp = head;
		head = head->next;
		delete temp;

		return true;
	}

	
	Node* prev = head;
	Node* cnode = head->next;
	while (cnode)
	{
		if (cnode->val == v)
		{
			prev->next = cnode->next;
			delete cnode;

			return true;
		}
		prev = cnode;
		cnode = cnode->next;
	}

	return false;
}

void
List::reverse()
{
	Node* cnode = head;
	Node* new_root = 0;

	while (cnode)
	{
		Node* next = cnode->next;
		cnode->next = new_root;
		new_root = cnode;
		cnode = next;
	}
	head = new_root;
}

