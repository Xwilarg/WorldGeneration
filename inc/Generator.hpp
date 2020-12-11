#pragma once

# include <SFML/Graphics.hpp>

# include "BlockType.hpp"

namespace WorldGeneration
{
    class Generator final
    {
    public:
        Generator(unsigned int xWin, unsigned int yWin, int blockSize) noexcept;
        void setBlock(int x, int y, BlockType block) noexcept;
        void draw(sf::RenderWindow& window) const noexcept;

    private:
        const unsigned int _xSize;
        const unsigned int _ySize;
        std::vector<std::vector<BlockType>> _world;
        std::vector<std::vector<sf::RectangleShape>> _renderWorld;
    };
}