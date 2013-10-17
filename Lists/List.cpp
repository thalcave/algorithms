#include "List.hpp"
#include <iostream>

List::List()
: head(0)
{
}

List::~List()
{
	if (hasCycle())
	{
		std::cerr<<"Cycle detected\n";
		return;
	}
	
	Node* cnode = head;
	while (cnode)
	{
		Node* prev = cnode;
		cnode = cnode->next;
		delete prev;
	}
}

bool
List::hasCycle() const
{
	//detect if a list has cycle: 
	// start with p1, step 1
	// 		p2, step 2
	
	if (!head)
	{
		return false;	//empty list has no cycle
	}
	
	Node* p1 = head;
	Node* p2 = head;
	
	bool cycle = false;
	
	do
	{
		p1 = p1->next;
		if (!p1)
		{	//no cycle
			break;
		}
		
		//move p2 with 2 positions
		p2 = p2->next;
		if (!p2)
		{
			break;
		}
		p2 = p2->next;
		if (!p2)
		{
			break;
		}
		
		//std::cout<<"*p1: "<<p1->val<<" *p2: "<<p2->val<<"\n";
		
		if (p1 == p2)
		{
			std::cout<<"found cycle: "<<p1->val<<"\n";
			cycle = true;
			break;
		}
	} while (true);
	
	if (!cycle)
	{
		return false;
	}
	
	//it has a cycle, find where it starts
	//if we rewind p1 to head and then go with both ptrs at same pace, they will meet at loop start
	p1 = head;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	std::cout<<"cycle begins at: "<<p1->val<<"\n";
	return true;
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

bool
List::insertElem(unsigned val, unsigned after)
{
	//search for after; if not found, return false
	if (!head)
	{
		return false;
	}
	
	Node* cnode = head;
	while (cnode && cnode->val != after)
	{
		cnode = cnode->next;
	}
	
	if (cnode)
	{
		Node* tmp = new Node(val);
		tmp->next = cnode->next;
		cnode->next = tmp;
		return true;
	}
	
	return false;
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
	Node* prev = 0;

	while (cnode)
	{
		Node* next = cnode->next;
		cnode->next = prev;
		prev = cnode;
		cnode = next;
	}
	head = prev;
}

void 
List::insertCycle(unsigned val, unsigned where)
{
	if (!head)
	{
		return;
	}
	
	Node* cnode = head;
	Node* wnode = 0;
	
	while (cnode->next)
	{
		if (cnode->val == where)
		{
			wnode = cnode;
		}

		cnode = cnode->next;
	}
	
	if (!wnode)
	{
		return;
	}
	
	//cnode is last element of list
	Node* tmp = new Node(val);
	cnode->next = tmp;
	tmp->next = wnode;
}

unsigned
List::size() const
{
	unsigned csize = 0;
	Node* cnode = head;
	while (cnode)
	{
		++csize;
		cnode = cnode->next;
	}
	
	return csize;
}


