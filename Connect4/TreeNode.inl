#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent) :
	mParent(parent), mEmpty(true), mDiscovered(false), mBeta(INT_MAX), mAlpha(INT_MIN)
{
}

// Should this be inline?
template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content) :
	mParent(parent), mContent(content), mEmpty(false), mDiscovered(false), mBeta(INT_MAX), mAlpha(INT_MIN)
{
}

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content, int alpha, int beta) :
	mParent(parent), mContent(content), mEmpty(false), mDiscovered(false), mBeta(beta), mAlpha(alpha)
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
