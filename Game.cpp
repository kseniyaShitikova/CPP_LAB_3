#include "Game.h"

Game::Game()
    : window(sf::VideoMode(512, 512), "GEMS")
{
    selected = false;
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();

        update();

        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;

            int col = x / board.getCellSize();
            int row = y / board.getCellSize();

            if (!selected)
            {
                selected = true;

                selectedRow = row;
                selectedCol = col;
            }
            else
            {
                if (board.areAdjacent(selectedRow, selectedCol, row, col))
                {
                    board.swapGems(selectedRow, selectedCol, row, col);

                    board.processBoard();
                }

                selected = false;
            }
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear();

    board.draw(window);

    window.display();
}