#pragma once

#include <vector>

template <typename T>
class TreeNode
{
public:

	TreeNode(const TreeNode* parent);
	~TreeNode();
	void setParent(const TreeNode* parent);
	void setContent(const T& content);
	void appendChild(const TreeNode* child);

	// retrun const pointer so node data cannot be altered
	const T* getContent();

private:
	TreeNode* mParent;
	T mContent;
	std::vector<TreeNode*> mChildren;
};
