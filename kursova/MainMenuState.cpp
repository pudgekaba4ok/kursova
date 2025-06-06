#include "MainMenuState.h"
#include "AssetManager.h"
#include "Command.h"
#include "Game.h"

MainMenuState::MainMenuState(Game& game) {

    if (!font.openFromFile("fonts/arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }

    float btnWidth = 220.f, btnHeight = 40.f;
    float startX = (1280 - btnWidth) / 2.f;
    float startY = 150.f;
    float gap = 85.f;

    sf::Text easyDificultyText(font, "Easy Difficult", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX - 240, startY + gap * 0),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<EasyDifficultyCommand>(),
        font,
        std::optional<sf::Text>(easyDificultyText)
    ));
    sf::Text mediumDificultyText(font, "Medium Difficult", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX, startY + gap * 0),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<MediumDifficultyCommand>(),
        font,
        std::optional<sf::Text>(mediumDificultyText)
    ));
    sf::Text HardDificultyText(font, "Hard Difficult", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX + 240, startY + gap * 0),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<HardDifficultyCommand>(),
        font,
        std::optional<sf::Text>(HardDificultyText)
    ));

    sf::Text continueGameText(font, "Continue", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX, startY + gap * 1),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<ContinueGameCommand>(),
        font,
        std::optional<sf::Text>(continueGameText)
    ));
    sf::Text showStatsText(font, "Stats", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX, startY + gap * 2),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<ShowStatsCommand>(),
        font,
        std::optional<sf::Text>(showStatsText)
        ));

    sf::Text showSettingsText(font, "Settings", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX, startY + gap * 3),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<ShowSettingsCommand>(),
        font,
        std::optional<sf::Text>(showSettingsText)
    ));

    sf::Text ExitTExt(font, "Exit", 20);
    buttons.emplace_back(std::make_unique<Button>(
        sf::Vector2f(startX, startY + gap * 4),
        sf::Vector2f(btnWidth, btnHeight),
        std::make_unique<ExitCommand>(),
        font,
        std::optional<sf::Text>(ExitTExt)
        ));

}

void MainMenuState::handleEvent(sf::Event& event, Game& game) {
    for (auto& btn : buttons) {
        btn->handleEvent(event, game);
    }
}

void MainMenuState::update(Game& game) {
    bool hasProgress = game.hasOngoingGame();
    buttons[3]->setEnabled(hasProgress);
}

void MainMenuState::render(sf::RenderWindow& window, Game& game) {
    window.clear(sf::Color(100, 100, 100));
    for (auto& btn : buttons) {
        btn->draw(window);
    }
    window.display();
}