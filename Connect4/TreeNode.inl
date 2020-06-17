#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent) :
	mParent(parent), mEmpty(true), mDiscovered(false)
{
}

// Should this be inline?
template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content) :
	mParent(parent), mContent(content), mEmpty(true), mDiscovered(false)
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
void TreeNode<T>::appendChild(const T& content)
{
	TreeNode<T>* child = new TreeNode<T>(this, content);
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
	if (mChildren(position).empty())
	{
		return nullptr;
	}

	return mChildren(position);
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
inline bool TreeNode<T>::isEmpty()
{
	return mEmpty;
}

template<typename T>
inline bool TreeNode<T>::isDiscovered()
{
	return mDiscovered;
}
