#pragma once

#include <vector>

template <typename T>
class TreeNode
{
public:

	TreeNode(TreeNode* parent);
	~TreeNode();
	void setParent(TreeNode* parent);
	void setContent(const T& content);
	void appendChild(TreeNode* child);

	// retrun const pointer so node data cannot be altered
	const T* getContent() const;

private:
	TreeNode* mParent;
	T mContent;
	std::vector<TreeNode*> mChildren;
};
#include "TreeNode.inl"

