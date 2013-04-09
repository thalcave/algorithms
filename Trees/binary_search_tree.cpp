#include "TreeNode.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>

void
addNode(TreeNode* parent, unsigned val, bool left)
{
	if (left)
	{
		parent->left = new TreeNode(val);
	}
	else
	{
		parent->right = new TreeNode(val);
	}
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
postOrder(TreeNode* root)
{
	if (root)
	{
		postOrder(root->left);
		postOrder(root->right);
		std::cout<<root->val<<" ";
	}
}

void
inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		std::cout<<root->val<<" ";
		inOrder(root->right);
		
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
insert(TreeNode*& node, unsigned val)
{
	if (!node)
	{
		node = new TreeNode(val);
		return;
	}

	if (node->val == val)
	{
		return;
	}

	if (node->val > val)
	{
		insert(node->left, val);
	}
	else
	{
		insert(node->right, val);
	}
}

bool
nonRecursiveSearch(TreeNode* root, unsigned search)
{
	if (!root)
	{
		return false;
	}

	TreeNode* cnode = root;
	while (cnode)
	{
		if (cnode->val == search)
			return true;

		if (cnode->val < search)
		{
			cnode = cnode->right;
		}
		else
		{
			cnode = cnode->left;
		}
	}

	return false;
}

bool
searchElem(TreeNode* node, unsigned search)
{
	//std::cout<<"searchElem: "<<search<<"\n";
	if (!node)
	{
		return false;
	}
	
	if (node->val == search)
	{
		std::cout<<"found: "<<&node<<"\n";
		return true;
	}

	return node->val > search ? searchElem(node->left, search) : searchElem(node->right, search);
	
}

//get biggest elem in this subtree
unsigned
getBiggestElem(TreeNode* node)
{
	if (!node)
	{
		throw std::runtime_error("invalid node");
	}
	
	if (!node->right)
	{
		return node->val;
	}
	
	return getBiggestElem(node->right);
}

unsigned
getSmallestElem(TreeNode* node)
{
	if (!node)
	{
		throw std::runtime_error("invalid node");
	}
	if (!node->left)
	{
		return node->val;
	}
	return getSmallestElem(node->left);
}


unsigned
findClosestElem(TreeNode* node)
{
	if (!node->left)
	{
		if (!node->right)
		{
			throw std::runtime_error("invalid node, has no children");
		}

		//only right
		return getSmallestElem(node->right);
	}

	if (!node->right)
	{
		return getBiggestElem(node->left);
	}
		
	unsigned biggest_left = getBiggestElem(node->left);
	unsigned smallest_right = getSmallestElem(node->right);

	return (node->val - biggest_left < smallest_right - node->val) ? biggest_left : smallest_right;
}


int main()
{
	//create tree node
	TreeNode* root = 0;
	insert(root, 1);
	insert(root, 8);
	insert(root, 3);
	insert(root, 4);
	insert(root, 6);
	insert(root, 7);
	insert(root, 10);
	insert(root, 13);
	insert(root, 14);
	insert(root, 14);
	insert(root, 15);
	
	std::cout<<"preOrder:";
	preOrder(root);
	std::cout<<"\n";

	std::cout<<"postOrder:";
	postOrder(root);
	std::cout<<"\n";

	std::cout<<"inOrder:";
	inOrder(root);
	std::cout<<"\n";

	std::cout<<"bfs:\n";
	bfs(root);
	std::cout<<"\n";

	{
		unsigned celem = 10;
		bool found = nonRecursiveSearch(root, celem);
		std::cout<<"found "<< celem << " : "<< (found? std::string("yes") : std::string("no"))<<std::endl;
	}

	{
		unsigned celem = 15;
		bool found = nonRecursiveSearch(root, celem);
		std::cout<<"found "<< celem << " : "<< (found? std::string("yes") : std::string("no"))<<std::endl;
	}
	{
		unsigned celem = 7;
		bool found = nonRecursiveSearch(root, celem);
		std::cout<<"found "<< celem << " : "<< (found? std::string("yes") : std::string("no"))<<std::endl;
	}

	unsigned closest = findClosestElem(root);
	std::cout<<"closest to root: "<<closest<<"\n";

	deleteTree(root);
	
	return 0;
}