#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"

class List
{
public:
	List();
	~List();
	void addElem(unsigned v);
	bool delElem(unsigned v);
	void print() const;

	void reverse();
private:
	Node* head;
};

#endif
