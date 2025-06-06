#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class MainMenuState : public GameState {
public:
    MainMenuState(Game& game);
    ~MainMenuState() = default;
    
    void handleEvent(sf::Event& event, Game& game) override;
    void update(Game& game) override;
    void render(sf::RenderWindow& window, Game& game) override;

private:

    sf::Font font;
    std::vector<std::unique_ptr<Button>> buttons;
};

#endif // MAINMENUSTATE_H