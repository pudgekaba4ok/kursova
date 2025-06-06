#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "GameState.h"
#include "Field.h"
#include "Button.h"
#include "IObserver.h"
#include <memory>
#include <vector>

class InGameState : public GameState {
public:
    InGameState(Game& game);
    ~InGameState() override;
    void setField(Field* f);
    void handleEvent(sf::Event& event, Game& game) override;
    void update(Game& game) override;
    void render(sf::RenderWindow& window, Game& game) override;

    // Called by Game when resuming from pause
    void resume(Game& game);

private:
    Field* field; // pointer to the current game field
    bool firstClick;
    bool isGameOver;
    bool isVictory;

    // Pause button (top-right)
    std::unique_ptr<Button> pauseButton;

    // For reporting win/lose to StatsManager via Observer
    void endGame(bool victory, Game& game);
};

#endif // INGAMESTATE_H
