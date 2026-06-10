#pragma once

#include "CellItem.h"
#include "GemColor.h"
#include <SFML/Graphics.hpp>
#include <memory>

const int ROWS = 8;
const int COLS = 8;
const int CELL_SIZE = 60;

class Board {
private:
    std::unique_ptr<CellItem> board[ROWS][COLS];

public:
    Board();
    ~Board() = default;

    void draw(sf::RenderWindow& window);
    sf::Color getSFMLColor(GemColor color);

    bool areAdjacent(int r1, int c1, int r2, int c2);
    void swapGems(int r1, int c1, int r2, int c2);
    bool trySwap(int r1, int c1, int r2, int c2);

    bool findMatches();
    void removeMatches();
    void dropGems();
    void processBoard();

    void applyRandomBonus(int row, int col);
    void setGemColor(int row, int col, GemColor color);
    void markForRemoval(int row, int col);

    int getRows() const;
    int getCols() const;
    int getCellSize() const;
    GemColor getGemColor(int row, int col) const;

private:
    void initEmptyBoard();
    void clearInitialMatches();
};