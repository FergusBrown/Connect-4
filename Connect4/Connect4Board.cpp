#include "Connect4Board.h"

/* why won't this work
Connect4Board::Connect4Board()
	:mWidth(7), mHeight(6)
{
}*/
// Treat 0,0 index as bottom left
// Iterate through column and find next available position
// Return if no available position
bool Connect4Board::addPiece(const size_t x, const Connect4::role &player)
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
			return true;
		}
	}

	return false;
}

// Check and return the winner
std::optional<Connect4::role> Connect4Board::checkVictory() const
{
	std::optional<Connect4::role> winner = std::nullopt;


	checkHoriz(winner);
	checkVert(winner);
	checkDiagL(winner);
	checkDiagR(winner);

	return winner;
}

// check if a particular palyer has one
bool Connect4Board::checkPlayerVictory(const Connect4::role& player) const
{
	std::optional<Connect4::role> victor = checkVictory();

	// I f an OR is used here will the first condition being true mean the next value is not checked?
	if (!victor.has_value() || victor.value() != player)
	{
		return false;
	}
	else {
		return true;
	}

	
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
bool Connect4Board::checkVert(std::optional<Connect4::role>& winner) const
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;
	std::optional<Connect4::role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++j) {
			temp = getItemAt(i, j);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
				case Connect4::role::P1:
					++P1_count;
					break;
				case Connect4::role::P2:
					++P2_count;
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
bool Connect4Board::checkHoriz(std::optional<Connect4::role>& winner) const
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;

	std::optional<Connect4::role> temp;

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < mWidth; ++j) {
			temp = getItemAt(j, i);

			if (!temp.has_value()) {
				break;
			}

			switch (temp.value()) {
			case Connect4::role::P1:
				++P1_count;
				break;
			case Connect4::role::P2:
				++P2_count;
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
bool Connect4Board::checkDiagL(std::optional<Connect4::role>& winner) const
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;
	std::optional<Connect4::role> temp;

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
			case Connect4::role::P1:
				++P1_count;
				break;
			case Connect4::role::P2:
				++P2_count;
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
			case Connect4::role::P1:
				++P1_count;
				break;
			case Connect4::role::P2:
				++P2_count;
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

bool Connect4Board::checkDiagR(std::optional<Connect4::role>& winner) const
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;
	std::optional<Connect4::role> temp;

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
			case Connect4::role::P1:
				++P1_count;
				break;
			case Connect4::role::P2:
				++P2_count;
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
			case Connect4::role::P1:
				++P1_count;
				break;
			case Connect4::role::P2:
				++P2_count;
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

bool Connect4Board::checkTurnValid(const Connect4::role& player) const
{
	unsigned int countP1 = 0;
	unsigned int countP2 = 0;

	for (auto& inner : mCells)
	{
		for (auto& cell : inner)
		{
			if (cell.has_value())
			{
				if (cell.value() == Connect4::role::P1)
				{
					++countP1;
				}
				else {
					++countP2;
				}
			}
		}
	}

	if (countP1 == countP2 && player == Connect4::role::P1)
	{
		return true;
	}

	if (countP1 > countP2 && player == Connect4::role::P2)
	{
		return true;
	}

	return false;
}
