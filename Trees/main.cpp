#include "TreeNode.hpp"
#include <iostream>
#include <queue>

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
		preOrder(root->left);
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
		std::cout<<"will delete: "<<root->val<<"\n";
		delete root;
	}
}

int main()
{
	//create tree node
	TreeNode* root = new TreeNode(1);
	addNode(root, 2, true);
	addNode(root, 3, false);

	addNode(root->left, 4, true);
	addNode(root->right, 5, true);

	addNode(root->right, 6, false);

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

	deleteTree(root);
	
	return 0;
}