#include "Connect4Board.h"
// Treat 0,0 index as bottom left
// Iterate through column and find next available position
// Return if no available position
bool Connect4Board::addPiece(const size_t x, const Connect4::role &player)
{
	if (x >= mWidth)
	{
		return false;
	}

	for (size_t i = 0; i < mHeight; i++)
	{
		if (mCells[x][i] == std::nullopt)
		{
			mCells[x][i].emplace(player);
			return true;
		}
	}

	return false;
}

std::optional<Connect4::role> Connect4Board::checkVictory()
{
	std::optional<Connect4::role> winner = std::nullopt;

	checkHoriz(winner);
	checkVert(winner);
	checkDiagL(winner);
	checkDiagR(winner);

	return winner;
}


bool Connect4Board::checkVert(std::optional<Connect4::role>& winner)
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;
	std::optional<Connect4::role> temp;

	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++j) {
			temp = getItemAt(i, j);

			if (temp == std::nullopt) {
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

bool Connect4Board::checkHoriz(std::optional<Connect4::role>& winner)
{
	unsigned int P1_count = 0;
	unsigned int P2_count = 0;

	std::optional<Connect4::role> temp;

	for (size_t i = 0; i < mHeight; ++i) {
		for (size_t j = 0; j < mWidth; ++j) {
			temp = getItemAt(j, i);

			if (temp == std::nullopt) {
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

bool Connect4Board::checkDiagL(std::optional<Connect4::role>& winner)
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

			if (temp == std::nullopt) {
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

			if (temp == std::nullopt) {
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

bool Connect4Board::checkDiagR(std::optional<Connect4::role>& winner)
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

			if (temp == std::nullopt) {
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

			if (temp == std::nullopt) {
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
