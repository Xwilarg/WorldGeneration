#include "Generator.hpp"

int main()
{
	constexpr unsigned int xWin = 1200, yWin = 500;
	constexpr int blockSize = 10;
	sf::RenderWindow window(sf::VideoMode(xWin, yWin), "WorldGeneration");

	auto generator = WorldGeneration::Generator(xWin, yWin, blockSize);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		generator.draw(window);
		window.display();
	}
	return 0;
}
