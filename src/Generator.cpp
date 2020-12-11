#include "Generator.hpp"

namespace WorldGeneration
{
    Generator::Generator(unsigned int xWin, unsigned int yWin, int blockSize) noexcept
        : _xSize(xWin / blockSize), _ySize(yWin / blockSize), _world(), _renderWorld()
    {
        // Fill the world with sky
        for (int y = 0; y < _ySize; y++)
        {
            std::vector<BlockType> line;
            std::vector<sf::RectangleShape> renderLine;
            for (int x = 0; x < _xSize; x++)
            {
                line.push_back(BlockType::SKY);
                auto renderShape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
                renderShape.setPosition(x * blockSize, y * blockSize);
                renderShape.setFillColor(sf::Color::Blue);
                renderLine.push_back(std::move(renderShape));
            }
            _world.push_back(std::move(line));
            _renderWorld.push_back(std::move(renderLine));
        }

        // Create the floor
        setBlock(0, _ySize - 1, BlockType::DIRT);
    }

    void Generator::setBlock(int x, int y, BlockType block) noexcept
    {
        _world[y][x] = block;
        _renderWorld[y][x].setFillColor(block == BlockType::SKY ? sf::Color::Blue : sf::Color::Red);
    }

    void Generator::draw(sf::RenderWindow& window) const noexcept
    {
        for (auto& line : _renderWorld)
        {
            for (auto& block : line)
            {
                window.draw(block);
            }
        }
    }
}