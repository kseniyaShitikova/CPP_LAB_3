#include "PaintBonus.h"
#include "Board.h"
#include <cstdlib>
#include <vector>
#include <cmath>

PaintBonus::PaintBonus(GemColor color)
    : sourceColor(color)
{
}

GemColor PaintBonus::getColor() const
{
    return sourceColor;
}

bool PaintBonus::isBonus() const
{
    return true;
}

void PaintBonus::setSourceColor(GemColor color)
{
    sourceColor = color;
}

void PaintBonus::activate(Board& board, int row, int col)
{
    int radius = 3;
    std::vector<std::pair<int, int>> validCells;

    for (int dr = -radius; dr <= radius; dr++)
    {
        for (int dc = -radius; dc <= radius; dc++)
        {
            if (dr == 0 && dc == 0) continue;

            int nr = row + dr;
            int nc = col + dc;

            if (nr < 0 || nr >= board.getRows() || nc < 0 || nc >= board.getCols())
                continue;

            bool isAdjacent = (abs(dr) == 1 && dc == 0) || (dr == 0 && abs(dc) == 1);

            if (!isAdjacent)
            {
                validCells.push_back({ nr, nc });
            }
        }
    }

    // Перекрашиваем целевую клетку
    board.setGemColor(row, col, sourceColor);

    // Перекрашиваем 2 случайные НЕсоседние клетки
    if (validCells.size() >= 2)
    {
        for (int i = 0; i < 2; i++)
        {
            int index = rand() % validCells.size();
            int targetRow = validCells[index].first;
            int targetCol = validCells[index].second;

            board.setGemColor(targetRow, targetCol, sourceColor);
        }
    }
}