#include "Cell.h"
#include "AssetManager.h"
#include <algorithm>

Cell::Cell(int x, int y, int size, int offsetX, int offsetY)
    : gridX(x), gridY(y), cellSize(size),
    mine(false), revealed(false), flagged(false), adjacentMines(0)
{
    sprite.emplace(AssetManager::getInstance().getTexture("cell_hidden"));

    sprite->setPosition({
        static_cast<float>(offsetX + gridX * cellSize),
        static_cast<float>(offsetY + gridY * cellSize)
        });

    float scale = static_cast<float>(cellSize) / 100.f;
    sprite->setScale({ scale, scale });

    updateSprite();
}

void Cell::setMine() {
    mine = true;
}

void Cell::setPosition(int x, int y) {
    if (sprite.has_value()) {
        sprite->setPosition({ static_cast<float>(x), static_cast<float>(y) });
    }
}

bool Cell::isMine() const {
    return mine;
}

void Cell::reveal() {
    if (revealed || flagged) return;
    revealed = true;
    updateSprite();
}

bool Cell::isRevealed() const {
    return revealed;
}

void Cell::toggleFlag() {
    if (revealed) return;
    flagged = !flagged;
    updateSprite();
}

bool Cell::isFlagged() const {
    return flagged;
}

void Cell::setAdjMines(int count) {
    adjacentMines = (mine) ? -1 : std::clamp(count, 0, 8);
}

int Cell::getAdjMines() const {
    return adjacentMines;
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}

void Cell::updateSprite() {
    AssetManager& assets = AssetManager::getInstance();
    sf::Vector2f oldPos = sprite->getPosition();
    float oldScale = sprite->getScale().x;

    if (!revealed) {
        if (flagged) {
            sprite.emplace(assets.getTexture("cell_flagged"));
        }
        else {
            sprite.emplace(assets.getTexture("cell_hidden"));
        }
    }
    else {
        if (mine) {
            sprite.emplace(assets.getTexture("mine"));
        }
        else {
            std::string key = "num_" + std::to_string(adjacentMines);
            sprite.emplace(assets.getTexture(key));
        }
    }

    sprite->setPosition(oldPos);
    sprite->setScale({ oldScale, oldScale });
}