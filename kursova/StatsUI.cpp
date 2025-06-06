#include "StatsUI.h"
#include "Game.h"
#include "StatsManager.h"
#include <stdexcept>

StatsUI::StatsUI(Game& game)
    : totalGames(StatsManager::getInstance().getGamesPlayed())
    , totalWins(StatsManager::getInstance().getWins())
    , font()
    , statsText()
{

    if (!font.openFromFile("fonts/arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }
    statsText.emplace(font, "Stats", 20);
    statsText->setFillColor(sf::Color::White);
    statsText->setPosition({ 100.f, 100.f });

    std::string statsString =
        "Games Played: " + std::to_string(totalGames) +
        "\nWins: " + std::to_string(totalWins) +
        "\nLosses: " + std::to_string(totalGames - totalWins) +
        "\n\nPress ESC to return.";
    statsText->setString(sf::String(statsString));

    StatsManager::getInstance().attach(this);
}

StatsUI::~StatsUI() {
    StatsManager::getInstance().detach(this);
}

void StatsUI::handleEvent(sf::Event& event, Game& game) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        game.popState();
    }
}

void StatsUI::update(Game& game) {
}

void StatsUI::render(sf::RenderWindow& window, Game& game) {
    window.clear(sf::Color(80, 80, 80));
    window.draw(*statsText);
    window.display();
}

void StatsUI::onStatsUpdated(int gamesPlayed, int wins) {
    totalGames = gamesPlayed;
    totalWins = wins;
    std::string statsString =
        "Games Played: " + std::to_string(totalGames) +
        "\nWins: " + std::to_string(totalWins) +
        "\nLosses: " + std::to_string(totalGames - totalWins) +
        "\n\nPress ESC to return.";
    statsText->setString(sf::String(statsString));
}