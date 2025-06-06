#include "PauseState.h"
#include "AssetManager.h"
#include "Command.h"
#include "Game.h"

PauseState::PauseState(Game& game) {
    // Use a font for “Resume”
    sf::Font font;
    if (!font.openFromFile("fonts/arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }
    sf::Text resumeText(font, "Resume", 20);
    resumeButton = std::make_unique<Button>(
        sf::Vector2f(350.f, 250.f),
        sf::Vector2f(100.f, 40.f),
        std::make_unique<ResumeGameCommand>(),
        font,
        std::optional<sf::Text>(resumeText)
    );
    sf::Text mainMenuText(font, "Main Menu", 20);
    mainMenuButton = std::make_unique<Button>(
        sf::Vector2f(350.f, 250.f),
        sf::Vector2f(100.f, 40.f),
        std::make_unique<ResumeGameCommand>(),
        font,
        std::optional<sf::Text>(mainMenuText)
    );

}

void PauseState::handleEvent(sf::Event& event, Game& game) {
    resumeButton->handleEvent(event, game);
	mainMenuButton->handleEvent(event, game);
}

void PauseState::update(Game& game) {
    // nothing else
}

void PauseState::render(sf::RenderWindow& window, Game& game) {
    
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    resumeButton->draw(window);
	mainMenuButton->draw(window);
}