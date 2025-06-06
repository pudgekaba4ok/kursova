#include "InGameState.h"
#include "AssetManager.h"
#include "Command.h"
#include "Game.h"
#include "LevelFactory.h"
#include "StatsManager.h"
#include <iostream>

InGameState::InGameState(Game& game)
    : firstClick(true), isGameOver(false), isVictory(false)
{
    

    LevelFactory::Difficulty diff = game.getSelectedDifficulty();
    field = LevelFactory::createField(diff);
    sf::Text pauseText(game.getFont(), "Pause", 20); 
    pauseButton = std::make_unique<Button>(
        sf::Vector2f(1100.f, 10.f),
        sf::Vector2f(80.f, 30.f),
        std::make_unique<ShowSettingsCommand>(),
        game.getFont(), 
        std::optional<sf::Text>(pauseText)

    );
}

InGameState::~InGameState() {
    delete field;
}

void InGameState::handleEvent(sf::Event& event, Game& game) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Escape) {
            game.changeState(Game::StateID::MainMenu);
            return;
        }
    }
    if (isGameOver) return;

    pauseButton->handleEvent(event, game);

    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left || mouseEvent->button == sf::Mouse::Button::Right) {

            sf::RenderWindow& win = game.getWindow();  // доступ до вікна
            sf::Vector2i mousePixel = sf::Mouse::getPosition(win);
            sf::Vector2f worldPos = win.mapPixelToCoords(mousePixel);

            int cellX = static_cast<int>((worldPos.x - field->getOffsetX()) / field->getCellSize());
            int cellY = static_cast<int>((worldPos.y - field->getOffsetY()) / field->getCellSize());

            if (cellX < 0 || cellX >= field->getWidth() ||
                cellY < 0 || cellY >= field->getHeight()) {
                return;
            }

            if (firstClick && mouseEvent->button == sf::Mouse::Button::Left) {
                field->placeMines(cellX, cellY);
                firstClick = false;
            }

            if (mouseEvent->button == sf::Mouse::Button::Left) {
                field->revealCell(cellX, cellY);
            }
            else {
                field->toggleFlag(cellX, cellY);
            }

            if (field->isMineRevealed()) {
                isGameOver = true;
                isVictory = false;
                endGame(false, game);
            }
            else if (field->checkVictory()) {
                isGameOver = true;
                isVictory = true;
                endGame(true, game);
            }
        }
    }
}

void InGameState::update(Game & game) {
}


void InGameState::setField(Field* f) {
    if (field) delete field;
    field = f;
    isGameOver = false;
    isVictory = false;
    firstClick = true;
}
void InGameState::render(sf::RenderWindow& window, Game& game) {
    window.clear(sf::Color(50, 50, 50));
    field->draw(window);
    pauseButton->draw(window);

    if (isGameOver) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        sf::Font font_abc = game.getFont();
        sf::Text text(font_abc);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setString(isVictory ? "You Win!" : "Game Over");

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({ textRect.position.x / 2, textRect.position.y / 2 });
        text.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });

        window.draw(text);
    }

    window.display();
}

void InGameState::resume(Game& game) {
    isGameOver = false;
    isVictory = false;
}

void InGameState::endGame(bool victory, Game& game) {
    StatsManager::getInstance().recordGameResult(victory);

    if (!victory) {
        field->revealAllMines();
    }

    isGameOver = true;
    isVictory = victory;
}