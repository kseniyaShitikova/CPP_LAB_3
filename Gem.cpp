#include "Gem.h"
#include <cstdlib>

Gem::Gem()
{
    color = randomColor();
    marked = false;
}

GemColor Gem::randomColor()
{
    int value = rand() % 5;

    switch (value)
    {
    case 0: return GemColor::Red;
    case 1: return GemColor::Green;
    case 2: return GemColor::Blue;
    case 3: return GemColor::Yellow;
    default: return GemColor::Purple;
    }
}