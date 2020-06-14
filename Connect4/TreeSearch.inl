#include "TreeSearch.h"

// Minimax algorithm from https://en.wikipedia.org/wiki/Minimax
template<typename Node>
inline int TreeSearch<Node>::minimax(const Node& gameState, const size_t depth, const bool maximisingPlayer) const
{
	int heuristicValue = heuristic(gameState);

	if (depth == 0 || isLeaf(gameState))
	{
		return heuristicValue;
	}

	if (maximisingPlayer)
	{
		value = -INFINITY;

		for (auto& child : *getChildren(gameState))
		{
			value = std::max(value, minimax(child, depth - 1, false));
			return value;
		}
	}
	else {
		value = INFINITY;

		for (auto& child : *getChildren(gameState))
		{
			value = std::max(value, minimax(child, depth - 1, true));
			return value;
		}
	}
}

template<typename Node>
inline std::vector<Node>* TreeSearch<Node>::getChildren(const Node& gameState) const
{
	return NULL;
}

// Evaluates the game state based on a defined heuristic
template<typename Node>
inline int TreeSearch<Node>::heuristic(const Node& gameState) const
{
	return INFINITY;
}

template<typename Node>
inline bool TreeSearch<Node>::isLeaf(const Node& gameState) const
{
	return false;
}

