#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
private:
    sf::RenderWindow window;

    Board board;

    bool selected;

    int selectedRow;
    int selectedCol;

public:
    Game();

    void run();

    void handleEvents();

    void update();

    void render();
};