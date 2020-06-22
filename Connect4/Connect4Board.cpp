#include <limits>
#include <algorithm>
#include <initializer_list>
#include "Connect4Board.h"
#include "TreeNode.h"

// REMOVE ONCE DONE
#include "Helper.h"

size_t Connect4Board::getBestMove(const int searchType, const int maxDepth) const
{
	switch (searchType) {
	case 0: 
		return depthFirstSearch(maxDepth);
		break;
	case 1:
		return alphaBetaSearch(maxDepth);
		break;
	case 2:
		return monteCarloSearch(maxDepth);
	default:
		return depthFirstSearch(maxDepth);
		break;
	}

}

Connect4Board::Connect4Board()
	: Grid<Connect4::Role>(7, 6)
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

std::stack<size_t> Connect4Board::getMoveHistory()
{
	return moveHistory;
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
			if (mCells[moveHistory.top()][mHeight - i - 1].has_value())
			{
				mCells[x][mHeight - i - 1].reset();
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

bool Connect4Board::checkDraw() const
{
	if (moveHistory.size() == (mWidth * mHeight))
	{
		return true;
	}
	else {
		return false;
	}

	
}

size_t Connect4Board::maxConnections(const Connect4::Role& player) const
{
	return std::max<size_t>({ countHoriz(player), countVert(player), countDiagL(player), countDiagR(player) });
}

size_t Connect4Board::countHoriz(const Connect4::Role& player) const
{
	size_t maxCount = 0;
	size_t count = 0;
	bool emptyPass = false;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < mWidth; ++j) {
			temp = getItemAt(j, i);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if (!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		emptyPass = false;
		count = 0;
	}

	return maxCount;
}

size_t Connect4Board::countVert(const Connect4::Role& player) const
{
	size_t maxCount = 0;
	size_t count = 0;
	bool emptyPass = false;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++j) {
			temp = getItemAt(i, j);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if (!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		emptyPass = false;
		count = 0;
	}

	return maxCount;
}

size_t Connect4Board::countDiagL(const Connect4::Role& player) const
{
	size_t maxCount = 0;
	size_t count = 0;
	bool emptyPass = false;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j + i, j);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if (!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		emptyPass = false;
		count = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(j, j + i);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if (!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		count = 0;
		emptyPass = false;
	}

	return maxCount;
}

size_t Connect4Board::countDiagR(const Connect4::Role& player) const
{
	size_t maxCount = 0;
	size_t count = 0;
	bool emptyPass = false;

	std::optional<Connect4::Role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j - i, j);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if (!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		emptyPass = false;
		count = 0;
	}

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < (mWidth - i); ++j) {
			if (j >= mHeight) {
				break;
			}

			temp = getItemAt(mWidth - 1 - j, j + i);

			if (!temp.has_value() && !emptyPass) {
				emptyPass = true;
				continue;
			}
			else if(!temp.has_value()) {
				emptyPass = false;
				break;
			}

			if (temp.value() == player)
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else {
				emptyPass = false;
				count = 0;
			}
		}
		emptyPass = false;
		count = 0;
	}

	return maxCount;
}

bool Connect4Board::checkTurnValid(const Connect4::Role& player) const
{

	if (checkVictory().has_value() || checkDraw())
	{
		return false;
	}



	if (checkPlayerTurn() ==  player)
	{
		return true;
	}


	return false;
}

// Create and traverse tree with depth first search -> https://en.wikipedia.org/wiki/Depth-first_search
// use minimax algorithm to evaluate each node and determine the best move -> https://en.wikipedia.org/wiki/Minimax
size_t Connect4Board::depthFirstSearch(const size_t maxDepth) const
{
	// Find current player to maximise 
	const Connect4::Role maximisingPlayerIdentity = checkPlayerTurn();
	Connect4::Role currentPlayer = maximisingPlayerIdentity;

	size_t depth = 0;
	const size_t moveCount = moveHistory.size();

	// This is the index of the child to a node
	size_t currentMove = 0;

	// Indicates whether current node should look to max or minimise
	// This should be flipped whenever depth increments or decrements
	bool maximisingPlayer = true;

	// Value to store in node
	int heuristicValue = INT_MIN;

	// Indicates a leaf node
	bool isLeaf = false;

	// Root node
	TreeNode<int>* root = new TreeNode<int>(nullptr, heuristicValue);

	// Vector to store tree traversal
	std::vector<TreeNode<int>*> tree;
	tree.push_back(root);
	
	// Create a board which is manipulated as the tree is traversed. This is used to evaluate board state;
	Connect4Board* tempBoard = new Connect4Board();
	*tempBoard = *this;

	// Traverse tree until parent is null (at root) AND all its possible children have been traversed
	while (tree.back()->hasParent() || currentMove < mWidth)
	{

		if (currentMove < mWidth && depth < maxDepth && !isLeaf)
		{
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
			}
		}
		else {

			// Perform Minimax and rollback if not at root
			if (tree.back()->hasParent())
			{
				if (!maximisingPlayer)
				{
					heuristicValue = std::max(tree.rbegin()[1]->getContent(), tree.back()->getContent());
				}
				else {
					heuristicValue = std::min(tree.rbegin()[1]->getContent(), tree.back()->getContent());
				}
				tree.rbegin()[1]->setContent(heuristicValue);

				tempBoard->rollBackMove();
				tree.pop_back();
			}
			
		}

		// Change node board details for current node
		currentMove = tree.back()->getChildrenSize();
		depth = tempBoard->getMoveHistory().size() - moveCount;
		isLeaf = (depth == maxDepth) || tempBoard->checkVictory().has_value() || tempBoard->checkDraw(); 


		if (isLeaf)
		{
			heuristicValue = tempBoard->evaluateBoard(currentPlayer);
			if (!maximisingPlayer)
			{
				heuristicValue = -heuristicValue;
			}
			tree.back()->setContent(heuristicValue);
		}

		currentPlayer = tempBoard->checkPlayerTurn();
		if (currentPlayer == maximisingPlayerIdentity)
		{
			maximisingPlayer = true;
		}
		else {
			maximisingPlayer = false;
		}

		
	}

	// Extract best move from the tree based on 
	size_t bestMove = 3;
	heuristicValue = root->getContent();
	for (size_t i = 0; i < root->getChildrenSize(); ++i)
	{
		if (root->getChild(i)->getContent() == heuristicValue)
		{
			bestMove = i;
			break;
		}
	}

	delete root;
	delete tempBoard;

	return bestMove;
}

// Immproved minimax with alpha beta pruning
size_t Connect4Board::alphaBetaSearch(const size_t maxDepth) const
{
	// Find current player to maximise 
	const Connect4::Role maximisingPlayerIdentity = checkPlayerTurn();
	Connect4::Role currentPlayer = maximisingPlayerIdentity;

	size_t depth = 0;
	const size_t moveCount = moveHistory.size();

	// This is the index of the child to a node
	size_t currentMove = 0;

	// Indicates whether current node should look to max or minimise
	// This should be flipped whenever depth increments or decrements
	bool maximisingPlayer = true;

	// Value to store in node
	int heuristicValue = INT_MIN;

	// Indicates a leaf node
	bool isLeaf = false;

	// Root node
	TreeNode<int>* root = new TreeNode<int>(nullptr, heuristicValue);

	// Vector to store tree traversal
	std::vector<TreeNode<int>*> tree;
	tree.push_back(root);

	// Create a board which is manipulated as the tree is traversed. This is used to evaluate board state;
	Connect4Board* tempBoard = new Connect4Board();
	*tempBoard = *this;

	// alpha beta setup
	int alpha = INT_MIN;
	int beta = INT_MAX;

	// Traverse tree until parent is null (at root) AND all its possible children have been traversed
	while (tree.back()->hasParent() || currentMove < mWidth)
	{

		if (currentMove < mWidth && depth < maxDepth && !isLeaf)
		{
			if (tempBoard->addPiece(tree.back()->getChildrenSize(), currentPlayer))
			{
				alpha = tree.back()->getAlpha();
				beta = tree.back()->getBeta();
				if (maximisingPlayer)
				{
					heuristicValue = INT_MAX;
					tree.back()->appendABChild(heuristicValue, alpha, beta);
				}
				else {
					heuristicValue = INT_MIN;
					tree.back()->appendABChild(heuristicValue, alpha, beta);
				}
				tree.push_back(tree.back()->getChild(currentMove));
			}
			else {
				tree.back()->appendEmptyChild();
			}
		}
		else {

			// Perform Minimax and rollback if not at root
			if (tree.back()->hasParent())
			{
				if (!maximisingPlayer)
				{
					// the node below will try to maximise
					heuristicValue = std::max(tree.rbegin()[1]->getContent(), tree.back()->getContent());
					alpha = tree.rbegin()[1]->getAlpha();
					tree.rbegin()[1]->setAlpha(std::max(alpha, heuristicValue));
				}
				else {
					// the node below will try to minimise
					heuristicValue = std::min(tree.rbegin()[1]->getContent(), tree.back()->getContent());
					beta = tree.rbegin()[1]->getBeta();
					tree.rbegin()[1]->setBeta(std::min(beta, heuristicValue));
					tree.rbegin()[1]->setBeta(std::min(beta, heuristicValue));
				}
				tree.rbegin()[1]->setContent(heuristicValue);

				tempBoard->rollBackMove();
				tree.pop_back();

				if (tree.back()->getAlpha() >=  tree.back()->getBeta())
				{
					//std::cout << "skip" << std::endl;
					int childNum = tree.back()->getChildrenSize();
					for (int i = childNum; i <= mWidth; ++i)
					{
						tree.back()->appendEmptyChild();
					}
				}
			}

		}

		// Change node board details for current node
		currentMove = tree.back()->getChildrenSize();
		depth = tempBoard->getMoveHistory().size() - moveCount;
		isLeaf = (depth == maxDepth) || tempBoard->checkVictory().has_value() || tempBoard->checkDraw();


		if (isLeaf)
		{
			heuristicValue = tempBoard->evaluateBoard(currentPlayer);
			if (!maximisingPlayer)
			{
				heuristicValue = -heuristicValue;
			}
			tree.back()->setContent(heuristicValue);
		}

		currentPlayer = tempBoard->checkPlayerTurn();
		if (currentPlayer == maximisingPlayerIdentity)
		{
			maximisingPlayer = true;
		}
		else {
			maximisingPlayer = false;
		}


	}

	// Extract best move from the tree based on 
	size_t bestMove = 3;
	heuristicValue = root->getContent();
	for (size_t i = 0; i < root->getChildrenSize(); ++i)
	{
		if (root->getChild(i)->getContent() == heuristicValue)
		{
			bestMove = i;
			break;
		}
	}

	delete root;
	delete tempBoard;

	return bestMove;
}

// A pure monte carlo search
size_t Connect4Board::monteCarloSearch(const size_t numPlayouts) const
{

	// Find current player to maximise 
	const Connect4::Role maximisingPlayerIdentity = checkPlayerTurn();
	Connect4::Role currentPlayer = maximisingPlayerIdentity;

	size_t depth = 0;
	const size_t moveCount = moveHistory.size();

	// This is the index of the child to a node
	size_t currentMove = 0;

	// Value to store in node
	int heuristicValue = INT_MIN;

	// Indicates a leaf node
	bool isLeaf = false;

	// Root node
	TreeNode<int>* root = new TreeNode<int>(nullptr, heuristicValue);

	// Vector to store tree traversal
	std::vector<TreeNode<int>*> tree;
	tree.push_back(root);

	// Create a board which is manipulated as the tree is traversed. This is used to evaluate board state;
	Connect4Board* tempBoard = new Connect4Board();
	*tempBoard = *this;

	// Traverse tree until parent is null (at root) AND all its possible children have been traversed
	while (tree.back()->hasParent() || currentMove < mWidth)
	{

		if (currentMove < mWidth && depth < maxDepth && !isLeaf)
		{
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
			}
		}
		else {
			// Perform Minimax and rollback if not at root
			if (tree.back()->hasParent())
			{
				if (!maximisingPlayer)
				{
					heuristicValue = std::max(tree.rbegin()[1]->getContent(), tree.back()->getContent());
				}
				else {
					heuristicValue = std::min(tree.rbegin()[1]->getContent(), tree.back()->getContent());
				}
				tree.rbegin()[1]->setContent(heuristicValue);

				tempBoard->rollBackMove();
				tree.pop_back();
			}

		}

		// Change node board details for current node
		currentMove = tree.back()->getChildrenSize();
		depth = tempBoard->getMoveHistory().size() - moveCount;
		isLeaf = (depth == maxDepth) || tempBoard->checkVictory().has_value() || tempBoard->checkDraw();

		if (isLeaf)
		{
			heuristicValue = tempBoard->evaluateBoard(currentPlayer);
			if (!maximisingPlayer)
			{
				heuristicValue = -heuristicValue;
			}
			tree.back()->setContent(heuristicValue);
		}

		currentPlayer = tempBoard->checkPlayerTurn();
		if (currentPlayer == maximisingPlayerIdentity)
		{
			maximisingPlayer = true;
		}
		else {
			maximisingPlayer = false;
		}
	}

	// Extract best move from the tree based on 
	size_t bestMove = 3;
	heuristicValue = root->getContent();
	for (size_t i = 0; i < root->getChildrenSize(); ++i)
	{
		if (root->getChild(i)->getContent() == heuristicValue)
		{
			bestMove = i;
			break;
		}
	}

	delete root;
	delete tempBoard;
	return bestMove;
}


// Evaluate the board state based on heuristic 1 in this paper -> https://www.researchgate.net/publication/331552609_Research_on_Different_Heuristics_for_Minimax_Algorithm_Insight_from_Connect-4_Game
int Connect4Board::evaluateBoard(const Connect4::Role player) const
{
	//size_t maxCount = board.maxConnections(player);
	size_t horizCount = countHoriz(player);
	size_t vertCount = countVert(player);
	size_t diagLCount = countDiagL(player);
	size_t diagRCount = countDiagR(player);
	size_t maxCount = std::max<size_t>({ vertCount, horizCount, diagLCount, diagRCount });

	int heuristicValue;

	switch (maxCount) {
	case 6:
		heuristicValue = INT_MAX;
		break;

	case 5:
		heuristicValue = INT_MAX;
		break;

	case 4:
		heuristicValue = INT_MAX;
		break;

	case 3:
		heuristicValue = featureTwo(player, horizCount, vertCount, diagLCount, diagRCount, maxCount);
		if (heuristicValue == INT_MAX)
		{
			break;
		}
		heuristicValue += featureThree(player) + featureFour(player);
		break;

	case 2:
		heuristicValue = featureThree(player) + featureFour(player);
		break;

	default:
		heuristicValue = featureFour(player);
		break;
	}

	return heuristicValue;
}

int Connect4Board::featureTwo(const Connect4::Role player, const size_t horiz, const size_t vert, const size_t diagL, const size_t diagR, const size_t max) const
{
	return 900000;
}

int Connect4Board::featureThree(const Connect4::Role player) const
{
	return 25000;
}

int Connect4Board::featureFour(const Connect4::Role player) const
{
	int score = 0;
	size_t height = getHeight();
	size_t width = getWidth();
	std::optional<Connect4::Role> square;

	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			square = getItemAt(i, height - 1 - j);
			if (square.has_value())
			{
				if (square.value() == player)
				{
					switch (i) {
					case 0:
						score += 40;
						break;
					case 1:
						score += 70;
						break;
					case 2:
						score += 120;
						break;
					case 3:
						score += 200;
						break;
					case 4:
						score += 120;
						break;
					case 5:
						score += 70;
						break;
					case 6:
						score += 40;
						break;
					}
				}
				else {
					break;
				}
				
			}
		}
	}

	return score;
}
