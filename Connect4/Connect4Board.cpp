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

	for (int i = 0; i < mHeight; i++)
	{
		if (mCells[x][i] == std::nullopt)
		{
			if (player == Connect4::PLAYER1)
			{
				mCells[x][i].emplace(Connect4::P1_PIECE);
			}
			else {
				mCells[x][i].emplace(Connect4::P2_PIECE);
			}
			return true;
		}
	}

	return false;
}
