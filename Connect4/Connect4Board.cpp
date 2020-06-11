#include "Connect4Board.h"
// Treat 0,0 index as bottom left
// Iterate through column and find next available position
// Return if no available position
bool Connect4Board::addPiece(const size_t x, const int player)
{
	if (x >= mWidth)
	{
		return false;
	}

	for (int i = 0; i < mHeight; i++)
	{
		if (mCells[x - 1][i] == std::nullopt)
		{
			mCells[x - 1][i].emplace(player);
		}
	}

	return false;
}
