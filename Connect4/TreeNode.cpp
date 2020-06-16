#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(const TreeNode* parent) :
	mParent(parent)
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
void TreeNode<T>::setParent(const TreeNode* parent)
{
	this->mParent = parent;
}

template<typename T>
void TreeNode<T>::setContent(const T& content)
{
	mContent = content;
}

template<typename T>
void TreeNode<T>::appendChild(const TreeNode* child)
{
	child->parent = this;
	mChildren.push_back(child);
}

template<typename T>
const T* TreeNode<T>::getContent()
{
	return &mContent;
}
