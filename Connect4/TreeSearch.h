#pragma once
#include <math.h>
#include <vector>
#include <algorithm>

template <typename ...> class TreeSearch;


template <typename Node, typename Move>
class TreeSearch <Node, Move>
{
public:
	// Constructor
	TreeSearch();

	// could also add a player type to pass in here, but expect that the gamestate class will be able to identify the player's turn
	Move bestMove(Node& gameState);

protected:
	int minimax(const Node& gameState, const size_t depth, const bool maximising) const;
	virtual std::vector<Node>* getChildren(const Node& gameState) const =0;
	virtual int heuristic(const Node& gameState) const =0;
	virtual bool isLeaf(const Node& gameState) const =0;
	virtual std::vector<Move>* getPossibleMoves(const Node& gameState) const =0;
	virtual Node* generateBoardState(const Move& move) const =0;
};
#include "TreeSearch.inl"

