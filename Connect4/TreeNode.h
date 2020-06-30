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
	void setEmpty(const bool empty);
	void setDiscovered();
	void setAlpha(const int value);
	void setBeta(const int value);
	void setVisitCount(const size_t value);
	void setWinCount(const size_t value);

	
	// Getter
	const T getContent() const;
	TreeNode<T>* getChild(int position);
	TreeNode<T>* getParent() const;
	size_t getChildrenSize() const;
	int getAlpha() const;
	int getBeta() const;
	size_t getVisitCount() const;
	size_t getWinCount() const;

	// Utility
	// - General
	bool hasParent();
	bool isEmpty();
	bool isDiscovered();
	void appendChild(T& content);
	void appendEmptyChild();
	void removeChildren();
	void removeChild(int pos);

	// - AB pruning
	void appendABChild(T& content, int alpha, int beta);

	// - MCTS
	double calcUCT() const;
	TreeNode<T>* getBestNodeUCT() const;

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

	// Variables for MC search: number of visits and playout wins
	size_t mVisitCount;
	size_t mWinCount;
};
#include "TreeNode.inl"

