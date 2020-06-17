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
	void setDiscovered();
	
	// Getter
	const T getContent() const;
	TreeNode<T>* getChild(int position);
	TreeNode<T>* getParent() const;
	size_t getChildrenSize() const;
	bool isEmpty();
	bool isDiscovered();

	void appendChild(T& content);
	void appendEmptyChild();




private:
	TreeNode* mParent;
	bool mEmpty;
	bool mDiscovered;
	// Could I make content a pointer to avoid needed the boolean to check if it is empty -> would that be a good idea?
	T mContent;
	std::vector<TreeNode*> mChildren;
};
#include "TreeNode.inl"

