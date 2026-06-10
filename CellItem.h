#pragma once

#include "GemColor.h"

class Board;  // forward declaration

class CellItem {
public:
    virtual ~CellItem() = default;

    virtual GemColor getColor() const = 0;
    virtual bool isBonus() const = 0;
    virtual void activate(Board& board, int row, int col);

    bool marked = false;  // для удаления при совпадениях
};