#include "List.hpp"

#include <iostream>

int main()
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
	
	
	return 0;
}