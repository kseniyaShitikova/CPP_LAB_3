#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
    Board board;

    int selectedRow;
    int selectedCol;
    bool hasSelected;

    void handleMouseClick(int mouseX, int mouseY);
    void processEvents();
    void render();

public:
    Game();
    void run();
};