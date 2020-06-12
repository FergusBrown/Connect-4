#include "Helper.h"

void help::displayConnect4(Connect4Board &board)
{
	size_t width = board.getWidth();
	size_t height = board.getHeight();

	std::optional<int> temp;
	for (size_t i = 1; i <= width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			temp = board.getItemAt(width - i, j);
			if (temp == std::nullopt)
			{
				std::cout << "  ";
			}
			else {
				std::cout << temp.value() << " ";
			}
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