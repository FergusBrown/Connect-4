#include "TreeSearch.h"

template<typename Node, typename Move>
inline Move TreeSearch<Node, Move>::bestMove(Node& gameState)
{
	// create a set of possible moves and corresponding board states then pass them to 
	//std::vector<Move> possibleMoves = getPossibleMoves(gameState);

	int bestValue = -INFINITY;
	Move nextMove;
	int temp;

	for (auto& move : getPossibleMoves(gameState))
	{
		int temp = minimax(generateBoardState(move), 0, false);
		if (temp > bestValue)
		{
			nextMove = move;
			bestValue = temp;
		}
	}

	return nextMove;
}

// Minimax algorithm from https://en.wikipedia.org/wiki/Minimax
template<typename Node, typename Move>
inline int TreeSearch<Node, Move>::minimax(const Node& gameState, const size_t depth, const bool maximisingPlayer) const
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

template<typename Node, typename Move>
inline std::vector<Node>* TreeSearch<Node, Move>::getChildren(const Node& gameState) const
{
	return NULL;
}

// Evaluates the game state based on a defined heuristic
template<typename Node, typename Move>
inline int TreeSearch<Node, Move>::heuristic(const Node& gameState) const
{
	return INFINITY;
}

template<typename Node, typename Move>
inline bool TreeSearch<Node, Move>::isLeaf(const Node& gameState) const
{
	return false;
}

template<typename Node, typename Move>
inline std::vector<Move>* TreeSearch<Node, Move>::getPossibleMoves(const Node& gameState) const
{
	return NULL;
}

template<typename Node, typename Move>
inline Node* TreeSearch<Node, Move>::generateBoardState(const Move& move) const
{
	return NULL;
}

