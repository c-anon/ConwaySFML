#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include<iostream>

constexpr auto width{ 800 };
constexpr auto height{ 600 };

uint16_t GetRandomNumber(uint16_t maxNumber);
std::array<std::array<sf::RectangleShape, width / 10>, height / 10> squares;
void CheckWhoDied(std::array<std::array<sf::RectangleShape, width / 10>, height / 10>& squares);
int LivingNeighbours(int x, int y, std::array<std::array<sf::RectangleShape, width / 10>, height / 10>& squares);
sf::Color GetBlackOrWhite();
/*std::random_device rd;
std::mt19937 g(rd()); */


int main()
{
	// create random squares on the board
	for (unsigned int i = 1; i < height / 10 - 1; ++i)
		for (unsigned int j = 1; j < width / 10 - 1; ++j)
		{
			squares[i][j].setSize({ 10, 10 });
			squares[i][j].setPosition(static_cast<float>(j * 10), static_cast<float>(i * 10));
			squares[i][j].setFillColor(GetBlackOrWhite());
		}

	sf::RenderWindow window(sf::VideoMode(width, height), "Conway's Game of Life");
	window.setFramerateLimit(10);
	// game loop

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		CheckWhoDied(squares);
		for (unsigned int i = 1; i < height / 10 - 1; ++i)
			for (unsigned int j = 1; j < width / 10 - 1; ++j)
			{
				window.draw(squares[i][j]);
			}
		window.display();

	}

}

uint16_t GetRandomNumber(uint16_t maxNumber)
{
	static std::random_device rd;
	static std::mt19937 g(rd());
	std::uniform_int_distribution<std::mt19937::result_type> distUINT16(0, maxNumber);
	return static_cast<uint16_t>(distUINT16(g));
}

void CheckWhoDied(std::array<std::array<sf::RectangleShape, width / 10>, height / 10>& blackSquares)
{
	for (unsigned int i = 1; i < height / 10 - 1; ++i)
		for (unsigned int j = 1; j < width / 10 - 1; ++j)
		{
			if (blackSquares[i][j].getFillColor() == sf::Color::Black) // if is alive
			{
				if (LivingNeighbours(i, j, blackSquares) != 2 && LivingNeighbours(i, j, blackSquares) != 3)
				{
					blackSquares[i][j].setFillColor(sf::Color::White); // die
				}
			}
			else // if is dead
			{
				if (LivingNeighbours(i, j, blackSquares) == 3)
				{
					blackSquares[i][j].setFillColor(sf::Color::Black); // ressurect
				}
			}
		}
}
int LivingNeighbours(int x, int y, std::array<std::array<sf::RectangleShape, width / 10>, height / 10>& blackSquares)
{
	int result = 0;

	if (blackSquares[x][y + 1].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x + 1][y + 1].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x + 1][y].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x + 1][y - 1].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x][y - 1].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x - 1][y - 1].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x - 1][y].getFillColor() == sf::Color::Black) result++;
	if (blackSquares[x - 1][y + 1].getFillColor() == sf::Color::Black) result++;
	return result;
}

sf::Color GetBlackOrWhite()
{
	uint16_t color{ GetRandomNumber(1) };
	if (color == 1)
	{
		return sf::Color::White;
	}
	else return sf::Color::Black;
}