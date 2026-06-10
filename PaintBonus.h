#pragma once

#include "CellItem.h"

class PaintBonus : public CellItem {
private:
    GemColor sourceColor;

public:
    PaintBonus(GemColor sourceColor);

    GemColor getColor() const override;
    bool isBonus() const override;
    void activate(Board& board, int row, int col) override;

    void setSourceColor(GemColor color);
};