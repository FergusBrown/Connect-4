#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent) :
	mParent(parent)
{
}

// Should this be inline?
template<typename T>
TreeNode<T>::TreeNode(TreeNode* parent, T& content) :
	mParent(parent), mContent(content)
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
}

template<typename T>
void TreeNode<T>::appendChild(TreeNode* child, const T& content)
{
	child->setParent(this);
	child->setContent(content);
	mChildren.push_back(child);
}

template<typename T>
const T* TreeNode<T>::getContent() const
{
	return &mContent;
}

template<typename T>
inline size_t TreeNode<T>::getChildrenSize() const
{
	return mChildren.size();
}
