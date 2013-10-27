#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"

class List
{
public:
	List();
	~List();
	//add elem at the end of the list
	void addElem(unsigned v);
	bool delElem(unsigned v);
	void print() const;
	
	//inserts elem after 'after'
	bool insertElem(unsigned val, unsigned after);

	void reverse();
	
	//add at the end 'val' and link it with 'where' element
	void insertCycle(unsigned val, unsigned where);
	
	bool hasCycle() const;
	
	//size of list
	unsigned size() const;
	
	typedef Node* NodePtr;
	const NodePtr& getHead() const { return head; }
	
	//eliminate duplicates in a list
	void elimDuplicates();
private:
	Node* head;
};

#endif
