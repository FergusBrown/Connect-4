#include "Helper.h"

// display board via command line
void help::displayConnect4(const Connect4Board &board)
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

// prompt player to take a turn
void help::playerPrompt(const Connect4::role& player)
{
	std::string name;

	if (player == Connect4::role::P1)
	{
		name = "Player 1";
	}
	else {
		name = "Player 2";
	}

	std::cout << name << ", please insert a valid column to place your piece:" << std::endl;
}

// Game loop for human players taking turns
void help::manualPlayLoop(Connect4Board& board)
{
	//Connect4::role player1, player2;

	help::displayConnect4(board);

	//player1 = Connect4::role::P1;
	//player2 = Connect4::role::P2;

	unsigned int input;

	while (!board.checkFinished())
	{
		help::playerPrompt(Connect4::PLAYER1);
		std::cin >> input;
		while (std::cin.fail() || input > board.getWidth()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			help::playerPrompt(Connect4::PLAYER1);
			std::cin >> input;
		}
		board.addPiece(input - 1, Connect4::PLAYER1);
		help::displayConnect4(board);

		if (board.checkFinished())
			break;

		help::playerPrompt(Connect4::PLAYER2);
		std::cin >> input;
		while (std::cin.fail() || input > board.getWidth()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			help::playerPrompt(Connect4::PLAYER2);
			std::cin >> input;
		}
		board.addPiece(input - 1, Connect4::PLAYER2);
		help::displayConnect4(board);
	}


	help::declareWinner(board);


}

// Any advantage of passing a pointer like this
void help::declareWinner(const Connect4Board& board)
{
	switch (board.checkVictory().value())
	{
	case Connect4::role::P1:
		std::cout << "P1 wins!" << std::endl;
		break;
	case Connect4::role::P2:
		std::cout << "P2 wins!" << std::endl;
		break;
	default:
		std::cout << "Nobody has won!" << std::endl;
	}
}
