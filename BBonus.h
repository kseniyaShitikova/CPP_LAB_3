#pragma once

#include "CellItem.h"

class BBonus : public CellItem {
private:
    GemColor color;

public:
    BBonus(GemColor color);

    GemColor getColor() const override;
    bool isBonus() const override;
    void activate(Board& board, int row, int col) override;
};