#pragma once
#include <limits>
#include <vector>

template <typename T>
class TreeNode
{
public:

	TreeNode(TreeNode* parent);
	TreeNode(TreeNode* parent, T& content);
	TreeNode(TreeNode* parent, T& content, int alpha, int beta);
	~TreeNode();

	// Setters
	void setParent(TreeNode* parent);
	void setContent(const T& content);
	void setDiscovered();
	void setAlpha(const int value);
	void setBeta(const int value);

	
	// Getter
	const T getContent() const;
	TreeNode<T>* getChild(int position);
	TreeNode<T>* getParent() const;
	size_t getChildrenSize() const;
	int getAlpha() const;
	int getBeta() const;

	// Utility
	bool hasParent();
	bool isEmpty();
	bool isDiscovered();

	void appendChild(T& content);
	void appendABChild(T& content, int alpha, int beta);
	void appendEmptyChild();

private:
	TreeNode* mParent;
	bool mEmpty;
	bool mDiscovered;
	// Could I make content a pointer to avoid needed the boolean to check if it is empty -> would that be a good idea?
	T mContent;
	std::vector<TreeNode*> mChildren;

	// Variables for alpha beta pruning
	int mAlpha;
	int mBeta;
};
#include "TreeNode.inl"

