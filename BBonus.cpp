#include "BBonus.h"
#include "Board.h"
#include <random>
#include <set>

BBonus::BBonus(GemColor color)
    : color(color)
{
}

GemColor BBonus::getColor() const
{
    return color;
}

bool BBonus::isBonus() const
{
    return true;
}

void BBonus::activate(Board& board, int row, int col)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rowDist(0, board.getRows() - 1);
    std::uniform_int_distribution<int> colDist(0, board.getCols() - 1);

    std::set<std::pair<int, int>> destroyedCells;

    while (destroyedCells.size() < 5)
    {
        int rr = rowDist(rng);
        int cc = colDist(rng);

        destroyedCells.insert({ rr, cc });
    }

    for (const auto& cell : destroyedCells)
    {
        board.markForRemoval(cell.first, cell.second);
    }

    board.markForRemoval(row, col);
}