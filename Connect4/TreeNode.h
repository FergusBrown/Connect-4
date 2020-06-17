#pragma once

#include <vector>

template <typename T>
class TreeNode
{
public:

	TreeNode(TreeNode* parent);
	TreeNode(TreeNode* parent, T& content);
	~TreeNode();

	// Setters
	void setParent(TreeNode* parent);
	void setContent(const T& content);
	
	// Getter
	const T getContent() const;
	TreeNode<T>* getChild(int position);
	TreeNode<T>* getParent() const;
	size_t getChildrenSize() const;
	bool empty();


	void appendChild(const T& content);
	void appendEmptyChild();




private:
	TreeNode* mParent;
	bool mEmpty;
	// Could I make content a pointer to avoid needed the boolean to check if it is empty -> would that be a good idea?
	T mContent;
	std::vector<TreeNode*> mChildren;
};
#include "TreeNode.inl"

