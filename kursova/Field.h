#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Field {
public:
    Field(int w, int h, int mines, int cSize = 10, int winW = 1280, int winH = 720);
    void revealAllMines();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getCellSize() const { return cellSize; }

    int getOffsetX() const { return offsetX; }
    int getOffsetY() const { return offsetY; }

    void placeMines(int firstX, int firstY);
    void revealCell(int x, int y);
    void toggleFlag(int x, int y);
    bool isMineRevealed() const;
    bool checkVictory() const;
    void draw(sf::RenderWindow& window);
    int getRemainingFlags() const { return totalMines - currentFlags; }
private:
    int currentFlags = 0;
    int width, height, totalMines, cellSize;
    bool minesPlaced;
    bool mineRevealed;
    std::vector<std::vector<Cell>> grid;
    int offsetX = 0;
    int offsetY = 0;

    void computeAdjacency();
    void floodReveal(int x, int y);
};

#endif // FIELD_H