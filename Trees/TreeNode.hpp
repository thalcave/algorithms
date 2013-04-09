#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

struct TreeNode
{
	unsigned val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(unsigned v): val(v), left(0), right(0) {}
};

#endif
