#include "GemItem.h"

GemItem::GemItem(GemColor color)
    : color(color)
{
}

GemColor GemItem::getColor() const
{
    return color;
}

bool GemItem::isBonus() const
{
    return false;
}