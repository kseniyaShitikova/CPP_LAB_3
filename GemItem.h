#pragma once

#include "CellItem.h"

class GemItem : public CellItem {
private:
    GemColor color;

public:
    GemItem(GemColor color);

    GemColor getColor() const override;
    bool isBonus() const override;
};