#pragma once

# include <SFML/Graphics.hpp>
# include <random>

# include "BlockType.hpp"

namespace WorldGeneration
{
    class Generator final
    {
    public:
        Generator(unsigned int xWin, unsigned int yWin, int blockSize) noexcept;
        void generateDirt(unsigned int x, unsigned int y) noexcept;
        void setBlock(unsigned int x, unsigned int y, BlockType block) noexcept;
        void draw(sf::RenderWindow& window) const noexcept;

    private:
        const unsigned int _xSize;
        const unsigned int _ySize;
        std::vector<std::vector<BlockType>> _world;
        std::vector<std::vector<sf::RectangleShape>> _renderWorld;
        std::random_device _device;
        std::mt19937 _rng;
        std::uniform_int_distribution<std::mt19937::result_type> _rand;
    };
}