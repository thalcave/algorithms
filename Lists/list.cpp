#include "List.hpp"
#include <iostream>

bool
convergentLists(const List& l1, const List& l2)
{
	if (l1.hasCycle())
	{
		std::cout<<"list1 has cycles\n";
		return false;
	}
	if (l2.hasCycle())
	{
		std::cout<<"list2 has cycles\n";
		return false;
	}
	
	unsigned sz1 = l1.size();
	unsigned sz2 = l2.size();
	
	//if a list is empty, they are not convergent
	if (!sz1 || !sz2)
	{
		std::cout<<"lists are not convergent (at least one of them is empty)\n";
		return false;
	}
	
	const Node* n1 = l1.getHead();
	const Node* n2 = l2.getHead();
	
	if (sz1 > sz2)
	{
		//move n1 with (sz1-sz2) positions
		unsigned moves = sz1 - sz2;
		while (moves && n1)
		{
			n1 = n1->next;
			--moves;
		}
	}
	else if (sz1 < sz2)
	{
		//move n2 with (sz2-sz1) positions
		unsigned moves = sz2 - sz1;
		while (moves && n2)
		{
			n2 = n2->next;
			--moves;
		}
	}
	
	//start of equal sequence
	const Node* start = 0;
	
	while (n1 && n2)
	{
		if (n1->val == n2->val)
		{
			if (!start)
			{
				start = n1;
			}
		}
		else
		{
			start = 0;
		}
		n1 = n1->next;
		n2 = n2->next;
	}
	
	if (start)
	{
		std::cout<<"Convergent list from : "<<start->val<<"\n";
		return true;
	}
	
	std::cout<<"Lists not convergent\n";
	return false;
}



int main()
{

	{
		List mlist;

		mlist.addElem(10);
		mlist.print();

		unsigned del(10);
		if (mlist.delElem(del))
		{
			std::cout<<"elem ["<<del<<"] deleted\n";
			mlist.print();
		}
		else
		{
			std::cout<<"elem ["<<del<<"] NOT FOUND\n";
		}

		mlist.addElem(13);
		mlist.addElem(15);
		mlist.addElem(16);
		mlist.addElem(17);
		mlist.addElem(18);
		mlist.addElem(19);
		mlist.addElem(20);
		mlist.print();

		del = 17;
		if (mlist.delElem(del))
		{
			std::cout<<"elem ["<<del<<"] deleted\n";
			mlist.print();
		}
		else
		{
			std::cout<<"elem ["<<del<<"] NOT FOUND\n";
		}

		mlist.reverse();
		std::cout<<"after reverse\n";
		mlist.print();
		
		mlist.insertElem(10, 13);
		std::cout<<"after insert (10,13)\n";
		mlist.print();
		
		mlist.insertElem(8, 13);
		std::cout<<"after insert (8,13)\n";
		mlist.print();
		
		mlist.reverse();
		std::cout<<"after reverse\n";
		mlist.print();
		
		mlist.insertCycle(5, 13);
		std::cout<<"after reverse\n";
		mlist.reverse();
		
	}
	
	{
		std::cout<<"Create lists\n";
		List l1;
		l1.addElem(1);
		l1.addElem(3);
		l1.addElem(5);
		l1.addElem(6);
		l1.addElem(7);
		l1.addElem(8);

		List l2;
		l2.addElem(1);
		l2.addElem(2);
		l2.addElem(3);
		l2.addElem(9);
		l2.addElem(6);
		l2.addElem(7);
		l2.addElem(8);
		l2.addElem(9);
		
		l1.print();
		l2.print();
		convergentLists(l1, l2);
	}

	return 0;
}
