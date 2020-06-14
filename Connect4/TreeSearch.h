#pragma once
#include <math.h>
#include <vector>
#include <algorithm>

template <typename Node>
class TreeSearch
{
public:
	int minimax(const Node& gameState, const size_t depth, const bool maximising) const;

protected:
	virtual std::vector<Node>* getChildren(const Node& gameState) const;
	virtual int heuristic(const Node& gameState) const;
	virtual bool isLeaf(const Node& gameState) const;
};
#include "TreeSearch.inl"

