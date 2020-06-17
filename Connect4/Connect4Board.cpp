#include <limits>
#include <algorithm>
#include <initializer_list>
#include "Connect4Board.h"
#include "TreeNode.h"

size_t Connect4Board::getBestMove()
{
	return depthFirstSearch();
}

 //why won't this work
Connect4Board::Connect4Board()
	: Grid<Connect4::Role>(7, 6), mMaxDepth(0)
{
}

// Treat 0,0 index as bottom left
// Iterate through column and find next available position
// Return if no available position
bool Connect4Board::addPiece(const size_t x, const Connect4::Role &player)
{
	if (x >= mWidth || !checkTurnValid(player) || mCells[x][mHeight-1].has_value())
	{
		return false;
	}

	for (size_t i = 0; i < mHeight; i++)
	{
		if (!mCells[x][i].has_value())
		{
			mCells[x][i].emplace(player);
			moveHistory.push(x);
			return true;
		}
	}

	return false;
}

// Check and return the winner
std::optional<Connect4::Role> Connect4Board::checkVictory() const
{
	std::optional<Connect4::Role> winner = std::nullopt;


	checkHoriz(winner);
	checkVert(winner);
	checkDiagL(winner);
	checkDiagR(winner);

	return winner;
}

// check if a particular palyer has one
bool Connect4Board::checkPlayerVictory(const Connect4::Role& player) const
{
	std::optional<Connect4::Role> victor = checkVictory();

	// I f an OR is used here will the first condition being true mean the next value is not checked?
	if (!victor.has_value() || victor.value() != player)
	{
		return false;
	}
	else {
		return true;
	}

	
}

Connect4::Role Connect4Board::checkPlayerTurn() const
{
	if (moveHistory.size() % 2 == 1)
	{
		return Connect4::PLAYER2;
	}
	else {
		return Connect4::PLAYER1;
	}
}

// roll back the last move
bool Connect4Board::rollBackMove()
{
	if (!moveHistory.empty())
	{
		size_t x = moveHistory.top();

		for (size_t i = 0; i < mHeight; ++i)
		{
			if (!mCells[moveHistory.top()][i].has_value())
			{
				mCells[x][i - 1].reset();
				moveHistory.pop();
				return true;
			}
		}
	}

	return false;
}

// check if game is finished
bool Connect4Board::checkFinished() const
{

	if (checkVictory().has_value())
	{
		return true;
	}

	for (auto& inner : mCells)
	{
		for (auto& cell : inner)
		{
			if (!cell.has_value())
			{
				return false;
			}
		}
	}

	return true;
}

// check for vertical connect 4
bool Connect4Board::checkVert(std::optional<Connect4::Role>& winner) const
{
	size_t P1_count = 0;
	size_t P2_count = 0;
	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++j) {
			temp = getItemAt(i, j);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
				case Connect4::PLAYER1:
					++P1_count;
					P2_count = 0;
					break;
				case Connect4::PLAYER2:
					++P2_count;
					P1_count = 0;
					break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	return false;
}

// check diagonals starting bottom right
bool Connect4Board::checkHoriz(std::optional<Connect4::Role>& winner) const
{
	size_t P1_count = 0;
	size_t P2_count = 0;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < mWidth; ++j) {
			temp = getItemAt(j, i);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::PLAYER1:
				++P1_count;
				P2_count = 0;
				break;
			case Connect4::PLAYER2:
				++P2_count;
				P1_count = 0;
				break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	return false;
}

// check diagonals starting bottom right
bool Connect4Board::checkDiagL(std::optional<Connect4::Role>& winner) const
{
	size_t P1_count = 0;
	size_t P2_count = 0;
	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j+i, j);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::PLAYER1:
				++P1_count;
				P2_count = 0;
				break;
			case Connect4::PLAYER2:
				++P2_count;
				P1_count = 0;
				break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j, j + i);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::PLAYER1:
				++P1_count;
				P2_count = 0;
				break;
			case Connect4::PLAYER2:
				++P2_count;
				P1_count = 0;
				break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	return false;
}

bool Connect4Board::checkDiagR(std::optional<Connect4::Role>& winner) const
{
	size_t P1_count = 0;
	size_t P2_count = 0;
	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j - i, j);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::PLAYER1:
				++P1_count;
				P2_count = 0;
				break;
			case Connect4::PLAYER2:
				++P2_count;
				P1_count = 0;
				break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j, j + i);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::PLAYER1:
				++P1_count;
				P2_count = 0;
				break;
			case Connect4::PLAYER2:
				++P2_count;
				P1_count = 0;
				break;
			}

			if (P1_count == 4 || P2_count == 4) {
				winner = temp;
				return true;
			}
		}
		P1_count = 0;
		P2_count = 0;
	}

	return false;
}

size_t Connect4Board::maxConnections(const Connect4::Role& player) const
{
	return std::max<size_t>({ countHoriz(player), countVert(player), countDiagL(player), countDiagR(player) });
}

size_t Connect4Board::countHoriz(const Connect4::Role& player) const
{
	size_t maxCount = 0;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < mWidth; ++j) {
			temp = getItemAt(j, i);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	return maxCount;
}

size_t Connect4Board::countVert(const Connect4::Role& player) const
{
	size_t maxCount = 0;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++j) {
			temp = getItemAt(i, j);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	return maxCount;
}

size_t Connect4Board::countDiagL(const Connect4::Role& player) const
{
	size_t maxCount = 0;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j + i, j);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j, j + i);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	return maxCount;
}

size_t Connect4Board::countDiagR(const Connect4::Role& player) const
{
	size_t maxCount = 0;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j - i, j);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j, j + i);

			if (!temp.has_value()) {
				break;
			}

			if (temp.value() == player)
			{
				++maxCount;
			}
			else {
				maxCount = 0;
			}
		}
		maxCount = 0;
	}

	return maxCount;
}

bool Connect4Board::checkTurnValid(const Connect4::Role& player) const
{
	size_t countP1 = 0;
	size_t countP2 = 0;

	for (auto& inner : mCells)
	{
		for (auto& cell : inner)
		{
			if (cell.has_value())
			{
				if (cell.value() == Connect4::PLAYER1)
				{
					++countP1;
				}
				else {
					++countP2;
				}
			}
		}
	}

	if (countP1 == countP2 && player == Connect4::PLAYER1)
	{
		return true;
	}

	if (countP1 > countP2 && player == Connect4::PLAYER2)
	{
		return true;
	}

	return false;
}

// Create and traverse tree with depth first search -> https://en.wikipedia.org/wiki/Depth-first_search
// use minimax algorithm to evaluate each node and determine the best move -> https://en.wikipedia.org/wiki/Minimax
size_t Connect4Board::depthFirstSearch() const
{
	// Find current player to maximise for
	Connect4::Role currentPlayer = checkPlayerTurn();

	// This is the index of the child to a node
	size_t currentMove = 0;

	// Indicates whether current node should look to max or minimise
	// This should be flipped whenever depth increments or decrements
	bool maximisingPlayer = true;
	int defaultValue = INT_MIN;

	// Value to store in node
	int heuristicValue = INT_MIN;

	// Root node
	TreeNode<int>* root = new TreeNode<int>(nullptr, heuristicValue);

	// Vector to store tree traversal
	std::vector<TreeNode<int>*> tree;
	tree.push_back(root);
	
	// Create a board which is manipulated as the tree is traversed. This is used to evaluate board state;
	Connect4Board* tempBoard = new Connect4Board();
	*tempBoard = *this;
	
	// Traverse tree until parent is null (at root) AND all its possible children have been traversed
	while (!(tree.back()->hasParent() && currentMove  >= mWidth))
	{


		if (tree.back()->isEmpty())
		{
			tree.back()->setParent(nullptr);
			tree.pop_back();

			if (!tree.back()->isDiscovered())
			{
				heuristicValue = evaluateBoard(*tempBoard);
				tree.back()->setContent(heuristicValue);
				tree.back()->setDiscovered();
			}

			// Perform minimax
			if (maximisingPlayer)
			{
				heuristicValue = std::max(tree.rbegin()[1]->getContent(), tree.back()->getContent());
			}
			else {
				heuristicValue = std::min(tree.rbegin()[1]->getContent(), tree.back()->getContent());
			}

			tree.rbegin()[1]->setContent(heuristicValue);
		}
		
		
		currentMove = tree.back()->getChildrenSize();

		if (currentMove < mWidth)
		{
			// create child and add it to the vector
			// If a pice can be added then create a child with a child with appropriate value
			// Otherwise create an empty child
			if (tempBoard->addPiece(tree.back()->getChildrenSize(), currentPlayer))
			{
				
				if (maximisingPlayer)
				{
					heuristicValue = INT_MAX;
					tree.back()->appendChild(heuristicValue);
				}
				else {
					heuristicValue = INT_MIN;
					tree.back()->appendChild(heuristicValue);
				}
				tree.push_back(tree.back()->getChild(currentMove));
			}
			else {
				tree.back()->appendEmptyChild();
				tree.push_back(tree.back()->getChild(currentMove));
			}
		}
		else {
			// All children have been evaluated
			// Rollback to previous node then and pop from vector
			tempBoard->rollBackMove();
			tree.back()->setParent(nullptr);
			tree.pop_back();
		}
		

	}

	// Flip minimax bool and change current player
	maximisingPlayer = !maximisingPlayer;
	if (currentPlayer == Connect4::PLAYER1)
	{
		currentPlayer = Connect4::PLAYER2;
	}
	else {
		currentPlayer = Connect4::PLAYER1;
	}

	// Extract best move from the tree based on 
	size_t bestMove = 3;
	heuristicValue = root->getContent();
	for (size_t i = 0; i < mWidth; ++i)
	{
		//if (root->getChild(i)->getContent() == heuristicValue)
		//{
		//	bestMove = i;
		//}
	}

	delete root;
	delete tempBoard;

	return bestMove;
}

// Evaluate the board state based on heuristic 1 in this paper -> https://www.researchgate.net/publication/331552609_Research_on_Different_Heuristics_for_Minimax_Algorithm_Insight_from_Connect-4_Game
int Connect4Board::evaluateBoard(const Connect4Board& board) const
{

	Connect4::Role turnPlayer = board.checkPlayerTurn();
	size_t maxCount = board.maxConnections(turnPlayer);

	int heuristicValue;


	switch (maxCount) {

	case 4:
		heuristicValue = INT_MAX;
		break;

	case 3:
		heuristicValue = featureTwo(board);
		if (heuristicValue == INT_MAX)
		{
			break;
		}
		heuristicValue += featureThree(board) + featureFour(board);
		break;

	case 2:
		heuristicValue = featureThree(board) + featureFour(board);
		break;

	default:
		heuristicValue = featureFour(board);
		break;
	}

	return heuristicValue;
}

int Connect4Board::featureTwo(const Connect4Board& board) const
{
	return 0;
}

int Connect4Board::featureThree(const Connect4Board& board) const
{
	return 0;
}

int Connect4Board::featureFour(const Connect4Board& board) const
{
	return 0;
}
