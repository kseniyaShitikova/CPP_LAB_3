#include "Board.h"
#include <queue>
#include <ctime>
#include <cstdlib>

Board::Board()
{
    srand(static_cast<unsigned>(time(nullptr)));

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            board[r][c] = Gem();
        }
    }
}

sf::Color Board::getSFMLColor(GemColor color)
{
    switch (color)
    {
    case GemColor::Red:
        return sf::Color::Red;

    case GemColor::Green:
        return sf::Color::Green;

    case GemColor::Blue:
        return sf::Color::Blue;

    case GemColor::Yellow:
        return sf::Color::Yellow;

    case GemColor::Purple:
        return sf::Color(180, 0, 255);

    default:
        return sf::Color::Black;
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            sf::RectangleShape rect;

            rect.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));

            rect.setPosition(c * CELL_SIZE, r * CELL_SIZE);

            rect.setFillColor(getSFMLColor(board[r][c].color));

            window.draw(rect);
        }
    }
}

bool Board::areAdjacent(int r1, int c1, int r2, int c2)
{
    return abs(r1 - r2) + abs(c1 - c2) == 1;
}

void Board::swapGems(int r1, int c1, int r2, int c2)
{
    std::swap(board[r1][c1], board[r2][c2]);
}

bool Board::findMatches()
{
    bool found = false;

    bool visited[ROWS][COLS] = {};

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (visited[r][c])
                continue;

            if (board[r][c].color == GemColor::Empty)
                continue;

            std::vector<std::pair<int, int>> group;

            std::queue<std::pair<int, int>> q;

            q.push({ r, c });

            visited[r][c] = true;

            GemColor currentColor = board[r][c].color;

            while (!q.empty())
            {
                auto current = q.front();
                q.pop();

                int cr = current.first;
                int cc = current.second;

                group.push_back({ cr, cc });

                for (int i = 0; i < 4; i++)
                {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];

                    if (nr < 0 || nc < 0 || nr >= ROWS || nc >= COLS)
                        continue;

                    if (visited[nr][nc])
                        continue;

                    if (board[nr][nc].color != currentColor)
                        continue;

                    visited[nr][nc] = true;

                    q.push({ nr, nc });
                }
            }

            if (group.size() >= 3)
            {
                found = true;

                for (auto& pos : group)
                {
                    board[pos.first][pos.second].marked = true;
                }
            }
        }
    }

    return found;
}

void Board::applyRandomBonus(int row, int col)
{
    int chance = rand() % 100;

    if (chance > 20)
        return;

    int type = rand() % 2;

    if (type == 0)
    {
        GemColor sourceColor = board[row][col].color;

        for (int i = 0; i < 3; i++)
        {
            int rr = rand() % ROWS;
            int cc = rand() % COLS;

            board[rr][cc].color = sourceColor;
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            int rr = rand() % ROWS;
            int cc = rand() % COLS;

            board[rr][cc].marked = true;
        }
    }
}

void Board::removeMatches()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c].marked)
            {
                applyRandomBonus(r, c);

                board[r][c].color = GemColor::Empty;

                board[r][c].marked = false;
            }
        }
    }
}

void Board::dropGems()
{
    for (int c = 0; c < COLS; c++)
    {
        int writeRow = ROWS - 1;

        for (int r = ROWS - 1; r >= 0; r--)
        {
            if (board[r][c].color != GemColor::Empty)
            {
                board[writeRow][c] = board[r][c];

                writeRow--;
            }
        }

        while (writeRow >= 0)
        {
            board[writeRow][c] = Gem();

            writeRow--;
        }
    }
}

void Board::processBoard()
{
    while (findMatches())
    {
        removeMatches();

        dropGems();
    }
}

int Board::getRows() const
{
    return ROWS;
}

int Board::getCols() const
{
    return COLS;
}

int Board::getCellSize() const
{
    return CELL_SIZE;
}