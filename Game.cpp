#include "Game.h"
#include <SFML/Window/Event.hpp>

Game::Game()
    : window(sf::VideoMode(COLS* CELL_SIZE, ROWS* CELL_SIZE), "GEMS")
    , selectedRow(-1)
    , selectedCol(-1)
    , hasSelected(false)
{
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    int row = mouseY / CELL_SIZE;
    int col = mouseX / CELL_SIZE;

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;

    if (!hasSelected)
    {
        // ѕервый клик Ч выбираем клетку
        selectedRow = row;
        selectedCol = col;
        hasSelected = true;
    }
    else
    {
        // ¬торой клик Ч пробуем обмен€ть
        if (board.areAdjacent(selectedRow, selectedCol, row, col))
        {
            board.trySwap(selectedRow, selectedCol, row, col);
        }

        // —брасываем выделение
        hasSelected = false;
        selectedRow = -1;
        selectedCol = -1;
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);
    board.draw(window);
    window.display();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        render();
    }
}