#include "Field.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <queue>
#include <utility>

Field::Field(int w, int h, int mines, int cSize, int winW, int winH)
    : width(w), height(h), totalMines(mines), cellSize(cSize),
    minesPlaced(false), mineRevealed(false)
{
    int fieldWidthPx = width * cellSize;
    int fieldHeightPx = height * cellSize;
    offsetX = (winW - fieldWidthPx) / 2;
    offsetY = (winH - fieldHeightPx) / 2;

    grid.reserve(height);

    for (int y = 0; y < height; ++y) {
        std::vector<Cell> row;
        row.reserve(width);
        for (int x = 0; x < width; ++x) {
            row.emplace_back(x, y, cellSize, offsetX, offsetY);
        }
        grid.push_back(std::move(row));
    }
}

void Field::placeMines(int avoidX, int avoidY) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int placed = 0;

    auto isInAvoidZone = [&](int x, int y) {
        return std::abs(x - avoidX) <= 1 && std::abs(y - avoidY) <= 1;
        };

    while (placed < totalMines) {
        int x = std::rand() % width;
        int y = std::rand() % height;

        if (!grid[y][x].isMine() && !isInAvoidZone(x, y)) {
            grid[y][x].setMine();
            ++placed;
        }
    }

     computeAdjacency();
}

void Field::computeAdjacency() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x].isMine()) {
                grid[y][x].setAdjMines(-1);
                continue;
            }
            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if (grid[ny][nx].isMine()) {
                            ++count;
                        }
                    }
                }
            }
            grid[y][x].setAdjMines(count);
        }
    }
}

void Field::revealCell(int x, int y) {
    if (grid[y][x].isFlagged() || grid[y][x].isRevealed()) return;

    grid[y][x].reveal();

    if (grid[y][x].isMine()) {
        mineRevealed = true;
        return;
    }

    if (grid[y][x].getAdjMines() == 0) {
        floodReveal(x, y);
    }
}

void Field::floodReveal(int startX, int startY) {
    std::queue<std::pair<int, int>> cellsToCheck;
    cellsToCheck.push({ startX, startY });

    while (!cellsToCheck.empty()) {
        auto [x, y] = cellsToCheck.front();
        cellsToCheck.pop();

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (!grid[ny][nx].isRevealed() && !grid[ny][nx].isMine()) {
                        grid[ny][nx].reveal();
                        if (grid[ny][nx].getAdjMines() == 0) {
                            cellsToCheck.push({ nx, ny });
                        }
                    }
                }
            }
        }
    }
}

void Field::toggleFlag(int x, int y) {
    if (grid[y][x].isRevealed()) return;

    if (!grid[y][x].isFlagged()) {
        if (currentFlags < totalMines) {
            grid[y][x].toggleFlag();
            ++currentFlags;
        }
    }
    else {
        grid[y][x].toggleFlag();
        --currentFlags;
    }
}

bool Field::isMineRevealed() const {
    return mineRevealed;
}

bool Field::checkVictory() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!grid[y][x].isMine() && !grid[y][x].isRevealed()) {
                return false;
            }
        }
    }
    return true;
}

void Field::draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].draw(window);
        }
    }
}
void Field::revealAllMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x].isMine()) {
                grid[y][x].reveal();
            }
        }
    }
}