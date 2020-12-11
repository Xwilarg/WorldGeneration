#include "Generator.hpp"

namespace WorldGeneration
{
    Generator::Generator(unsigned int xWin, unsigned int yWin, int blockSize) noexcept
        : _xSize(xWin / blockSize), _ySize(yWin / blockSize), _world(), _renderWorld(),
        _device(), _rng(_device()), _rand(1, 100)
    {
        // Fill the world with sky
        for (unsigned int y = 0; y < _ySize; y++)
        {
            std::vector<BlockType> line;
            std::vector<sf::RectangleShape> renderLine;
            for (unsigned int x = 0; x < _xSize; x++)
            {
                line.push_back(BlockType::SKY);
                auto renderShape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
                renderShape.setPosition(static_cast<float>(x * blockSize), static_cast<float>(y * blockSize));
                renderShape.setFillColor(sf::Color::Blue);
                renderLine.push_back(std::move(renderShape));
            }
            _world.push_back(std::move(line));
            _renderWorld.push_back(std::move(renderLine));
        }

        // Create the floor
        for (unsigned int x = 0; x < _xSize; x++)
            generateDirt(x, _ySize - 1);
    }

    void Generator::generateDirt(unsigned int x, unsigned int y) noexcept
    {
        if (x < 0 || y < 0 || x >= _xSize || y >= _ySize || _world[y][x] == BlockType::DIRT) // Out of range or already dirt
            return;

        setBlock(x, y, BlockType::DIRT);

        if (_rand(_rng) < (20 + ((_ySize - y) * 5)))
            return;

        generateDirt(x - 1, y);
        generateDirt(x + 1, y);
        generateDirt(x, y - 1);
        generateDirt(x, y + 1);
    }

    void Generator::setBlock(unsigned int x, unsigned int y, BlockType block) noexcept
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