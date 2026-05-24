#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Gem.h"

class Board
{
private:
    static const int ROWS = 8;
    static const int COLS = 8;
    static const int CELL_SIZE = 64;

    Gem board[ROWS][COLS];

public:
    Board();

    void draw(sf::RenderWindow& window);

    bool areAdjacent(int r1, int c1, int r2, int c2);

    void swapGems(int r1, int c1, int r2, int c2);

    bool findMatches();

    void removeMatches();

    void dropGems();

    void processBoard();

    void applyRandomBonus(int row, int col);

    sf::Color getSFMLColor(GemColor color);

    int getRows() const;
    int getCols() const;
    int getCellSize() const;
};