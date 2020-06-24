#include "TreeNode.h"
#include <math.h>

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent) :
	mParent(parent), mEmpty(true), mDiscovered(false)
	, mBeta(INT_MAX), mAlpha(INT_MIN)
	, mVisitCount(0), mWinCount(0)
{
}

// Should this be inline?
template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content) :
	mParent(parent), mContent(content), mEmpty(false), mDiscovered(false)
	, mBeta(INT_MAX), mAlpha(INT_MIN)
	, mVisitCount(0), mWinCount(0)
{
}

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content, int alpha, int beta) :
	mParent(parent), mContent(content), mEmpty(false), mDiscovered(false)
	, mBeta(beta), mAlpha(alpha)
	, mVisitCount(0), mWinCount(0)
{
}

// Delete all children so that delete only ever needs to be called on the root
template<typename T>
inline TreeNode<T>::~TreeNode()
{
	for (auto* child : mChildren)
	{
		delete child;
	}
}

template<typename T>
void TreeNode<T>::setParent(TreeNode* parent)
{
	this->mParent = parent;
}

template<typename T>
void TreeNode<T>::setContent(const T& content)
{
	mContent = content;
	mEmpty = false;
}

template<typename T>
inline void TreeNode<T>::setDiscovered()
{
	mDiscovered = true;
}

template<typename T>
inline void TreeNode<T>::setAlpha(const int value)
{
	mAlpha = value;
}

template<typename T>
inline void TreeNode<T>::setBeta(const int value)
{
	mBeta = value;
}

template<typename T>
inline void TreeNode<T>::setVisitCount(const size_t value)
{
	mVisitCount = value;
}

template<typename T>
inline void TreeNode<T>::setWinCount(const size_t value)
{
	mWinCount = value;
}

template<typename T>
void TreeNode<T>::appendChild(T& content)
{
	TreeNode<T>* child = new TreeNode<T>(this, content);
	mChildren.push_back(child);
}

template<typename T>
inline void TreeNode<T>::appendABChild(T& content, int alpha, int beta)
{
	TreeNode<T>* child = new TreeNode<T>(this, content, alpha, beta);
	mChildren.push_back(child);
}

template<typename T>
inline void TreeNode<T>::appendEmptyChild()
{
	TreeNode<T>* child = new TreeNode<T>(this);

	mChildren.push_back(child);
}

template<typename T>
double TreeNode<T>::calcUCT() const
{
	if (mVisitCount == 0)
	{
		return DBL_MAX;
	}

	size_t parentVisits = mParent->getVisitCount();
	double c = 1.41421356237;

	double result = mWinCount / mVisitCount + c * sqrt( log(parentVisits) / mVisitCount);

	return result;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getBestNodeUCT() const
{
	TreeNode<T>* bestNode = nullptr;
	double maxUCT = 0;
	double temp;

	for (auto* child : mChildren)
	{
		temp = child->calcUCT();
		if (temp > maxUCT)
		{
			maxUCT = temp;
			bestNode = child;
		}
	}

	return bestNode;
}

// need some sort of error protection here
template<typename T>
const T TreeNode<T>::getContent() const
{
	return mContent;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::getChild(int position)
{
		return mChildren[position];
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::getParent() const
{
	return mParent;
}

template<typename T>
inline size_t TreeNode<T>::getChildrenSize() const
{
	return mChildren.size();
}

template<typename T>
inline int TreeNode<T>::getAlpha() const
{
	return mAlpha;
}

template<typename T>
inline int TreeNode<T>::getBeta() const
{
	return mBeta;
}

template<typename T>
inline size_t TreeNode<T>::getVisitCount() const
{
	return mVisitCount;
}

template<typename T>
inline size_t TreeNode<T>::getWinCount() const
{
	return mWinCount;
}

template<typename T>
bool TreeNode<T>::hasParent()
{
	if (mParent == nullptr)
	{
		return false;
	}
	else {
		return true;
	}
}

template<typename T>
inline bool TreeNode<T>::isEmpty()
{
	return mEmpty;
}

template<typename T>
inline bool TreeNode<T>::isDiscovered()
{
	return mDiscovered;
}
