#include "Board.h"
#include "GemItem.h"      
#include "BBonus.h"        
#include "PaintBonus.h" 
#include "ItemFactory.h"
#include <queue>
#include <random>
#include <ctime>
#include <cmath>

Board::Board()
{
    initEmptyBoard();
    clearInitialMatches();
}

void Board::initEmptyBoard()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            board[r][c] = ItemFactory::createRandomGem();
        }
    }
}

void Board::clearInitialMatches()
{
    // Убираем начальные совпадения
    while (findMatches())
    {
        removeMatches();
        dropGems();
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
    case GemColor::Empty:
        return sf::Color(50, 50, 50);
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
            rect.setFillColor(getSFMLColor(board[r][c]->getColor()));
            window.draw(rect);

            // Если это бонус — рисуем белую рамку
            if (board[r][c]->isBonus())
            {
                sf::RectangleShape outline;
                outline.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                outline.setPosition(c * CELL_SIZE, r * CELL_SIZE);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineColor(sf::Color::White);
                outline.setOutlineThickness(3);
                window.draw(outline);
            }
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

bool Board::trySwap(int r1, int c1, int r2, int c2)
{
    if (!areAdjacent(r1, c1, r2, c2))
        return false;

    swapGems(r1, c1, r2, c2);

    if (findMatches())
    {
        processBoard();
        return true;
    }
    else
    {
        swapGems(r1, c1, r2, c2);
        return false;
    }
}

bool Board::findMatches()
{
    bool found = false;
    bool visited[ROWS][COLS] = {};

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    // Сначала сбрасываем старые метки
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            board[r][c]->marked = false;
        }
    }

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (visited[r][c]) continue;

            GemColor currentColor = board[r][c]->getColor();
            if (currentColor == GemColor::Empty) continue;

            // BFS для поиска группы
            std::vector<std::pair<int, int>> group;
            std::queue<std::pair<int, int>> q;

            q.push({ r, c });
            visited[r][c] = true;

            while (!q.empty())
            {
                auto [cr, cc] = q.front();
                q.pop();

                group.push_back({ cr, cc });

                for (int i = 0; i < 4; i++)
                {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];

                    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
                    if (visited[nr][nc]) continue;
                    if (board[nr][nc]->getColor() != currentColor) continue;

                    visited[nr][nc] = true;
                    q.push({ nr, nc });
                }
            }

            // Если группа из 3 и более — помечаем на удаление
            if (group.size() >= 3)
            {
                found = true;
                for (size_t i = 0; i < group.size(); i++)
                {
                    int gr = group[i].first;
                    int gc = group[i].second;
                    board[gr][gc]->marked = true;
                }
            }
        }
    }

    return found;
}

void Board::applyRandomBonus(int row, int col)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> chanceDist(0, 99);
    std::uniform_int_distribution<int> bonusDist(0, 1);

    int chance = chanceDist(rng);
    if (chance > 20) return;  // 20% шанс выпадения бонуса

    GemColor sourceColor = board[row][col]->getColor();

    auto bonus = ItemFactory::createRandomBonus(sourceColor);

    // Сохраняем бонус в клетку
    board[row][col] = std::move(bonus);
}

void Board::removeMatches()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c]->marked)
            {
                applyRandomBonus(r, c);
                board[r][c] = ItemFactory::createRandomGem();  // ? новый камень
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
            if (board[r][c]->getColor() != GemColor::Empty)
            {
                if (writeRow != r)
                {
                    board[writeRow][c] = std::move(board[r][c]);
                }
                writeRow--;
            }
        }

        while (writeRow >= 0)
        {
            board[writeRow][c] = ItemFactory::createRandomGem();
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

void Board::setGemColor(int row, int col, GemColor color)
{
    // Создаём новый камень с нужным цветом
    board[row][col] = std::make_unique<GemItem>(color);
}

void Board::markForRemoval(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        board[row][col]->marked = true;
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

GemColor Board::getGemColor(int row, int col) const
{
    return board[row][col]->getColor();
}