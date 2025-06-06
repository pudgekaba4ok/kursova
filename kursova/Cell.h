#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <optional>

class Cell {
public:
    Cell(int x, int y, int size, int offsetX = 0, int offsetY = 0);

    void setMine();
    bool isMine() const;
    void setPosition(int x, int y);
    void reveal();
    bool isRevealed() const;

    void toggleFlag();
    bool isFlagged() const;

    void setAdjMines(int count);
    int getAdjMines() const;

    void draw(sf::RenderWindow& window);

private:
    int gridX, gridY;   
    int cellSize;       
    bool mine;
    bool revealed;
    bool flagged;
    int adjacentMines;

    std::optional<sf::Sprite> sprite;
    void updateSprite();
};

#endif // CELL_H