
#pragma once
#include "GameState.h"
#include "Button.h"
#include <memory>

class PauseState : public GameState {
public:
    explicit PauseState(Game& game);

    void handleEvent(sf::Event& event, Game& game) override;
    void update(Game& game) override;
    void render(sf::RenderWindow& window, Game& game) override;

private:
    std::unique_ptr<Button> resumeButton;
    std::unique_ptr<Button> mainMenuButton; 
};