#pragma once

enum class GemColor
{
    Red,
    Green,
    Blue,
    Yellow,
    Purple,
    Empty
};

class Gem
{
public:
    GemColor color;
    bool marked;

    Gem();

    static GemColor randomColor();
};