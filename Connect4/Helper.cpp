#include "Helper.h"

void help::displayConnect4(Connect4Board &board)
{
	size_t width = board.getWidth();
	size_t height = board.getHeight();

	std::optional<Connect4::role> temp;
	char piece;

	for (size_t i = 0; i < width; ++i)
	{
		std::cout << "_ ";
	}
	std::cout << std::endl;

	for (size_t i = 1; i <= height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			temp = board.getItemAt(j, height - i);
			if (!temp.has_value())
			{
				piece = ' ';
			}
			else {
				switch (temp.value()) {
				case Connect4::role::P1:
					piece = help::P1_PIECE;
					break;
				case Connect4::role::P2:
					piece = help::P2_PIECE;
					break;
				default:
					piece = ' ';
					break;
				}
			}
			std::cout << piece << " ";
		}
		std::cout << std::endl;
	}


	for (size_t i = 0; i < width; ++i)
	{
		std::cout << i + 1 << " ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < width; ++i)
	{
		std::cout << "_ ";
	}
	std::cout << std::endl;
}

void help::playerPrompt(Connect4::role& player)
{
	std::string name;

	if (player == Connect4::role::P1)
	{
		name = "Player 1";
	}
	else {
		name = "Player 2";
	}

	std::cout << name << ", please insert a valid column to place your piece:";
}
