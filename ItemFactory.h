#pragma once

#include <memory>
#include "CellItem.h"

class ItemFactory {
public:
    static std::unique_ptr<CellItem> createRandomGem();
    static std::unique_ptr<CellItem> createRandomBonus(GemColor sourceColor = GemColor::Red);
};