#include "ItemFactory.h"
#include "GemItem.h"
#include "PaintBonus.h"
#include "BBonus.h"
#include <random>

std::unique_ptr<CellItem> ItemFactory::createRandomGem()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> colorDist(0, 4);

    GemColor color = static_cast<GemColor>(colorDist(rng));
    return std::make_unique<GemItem>(color);
}

std::unique_ptr<CellItem> ItemFactory::createRandomBonus(GemColor sourceColor)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> typeDist(0, 1);

    if (typeDist(rng) == 0)
    {
        auto bonus = std::make_unique<PaintBonus>(sourceColor);
        bonus->setSourceColor(sourceColor);
        return bonus;
    }
    else
    {
        return std::make_unique<BBonus>(sourceColor);
    }
}