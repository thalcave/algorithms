#include "TreeNode.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>
#include <stdlib.h>
#include <algorithm>
#include "../common/GenVector.hpp"

//create BST with minimal height from sorted array
TreeNode*
createBST(const IntVector& vect, unsigned left, unsigned right)
{
	if (right < left)
	{
		throw std::logic_error("Invalid index, right is smaller than left");
	}
	//take middle element
	unsigned middle = (right - left)/2 + left;
	TreeNode* croot = new TreeNode(vect.at(middle));
	
	if (right != left)	//single element
	{
		if (middle > left)
		{
			//go in first half of array
			croot->left = createBST(vect, left, middle - 1);
		}
		if (middle < right)
		{
			//go in second half of array
			croot->right = createBST(vect, middle+1, right);
		}
	}

	return croot;
}

//pre: root, left, right
void
preOrder(TreeNode* root)
{
	if (root)
	{
		std::cout<<root->val<<" ";
		std::cout<<"go left\n";
		preOrder(root->left);
		std::cout<<"go right\n";
		preOrder(root->right);
		
	}
}

void
bfs(TreeNode* root)
{
	if (!root)
	{
		return;
	}

	typedef std::queue<TreeNode*> NodeQueue;
	NodeQueue nqueue;

	nqueue.push(root);
	while (!nqueue.empty())
	{
		NodeQueue::size_type qsize = nqueue.size();
		for (NodeQueue::size_type i = 0; i < qsize; ++i)
		{
			TreeNode* cnode = nqueue.front();
			nqueue.pop();

			std::cout<<cnode->val<<" ";
			if (cnode->left)
			{
				nqueue.push(cnode->left);
			}
			if (cnode->right)
			{
				nqueue.push(cnode->right);
			}
		}
		std::cout<<"\n";
	}
}

void
deleteTree(TreeNode* root)
{
	if (root)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		//std::cout<<"will delete: "<<root->val<<"\n";
		delete root;
	}
}

void
createTree(const IntVector& vect)
{
	if (vect.empty())
	{
		throw std::logic_error("Empty input vector");
	}
	std::cout<<"Create tree from vector: ";
	printVector(vect);
	
	//create tree node
	TreeNode* root = createBST(vect, 0, vect.size()-1);
	bfs(root);
	
	deleteTree(root);
	
	std::cout<<"----------------------------------------------------\n";

}

int main()
{
	//IntVector vect = generateVector();
	{
		IntVector vect(1, 10);
		std::sort(vect.begin(), vect.end());

		createTree(vect);
	}
	
	{
		IntVector vect;
		vect.push_back(10);
		vect.push_back(20);
		std::sort(vect.begin(), vect.end());

		createTree(vect);
	}

	
	{
		IntVector vect = generateVector();
		std::sort(vect.begin(), vect.end());

		createTree(vect);
	}
	
	return 0;
}
