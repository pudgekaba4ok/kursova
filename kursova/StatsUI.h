#ifndef STATSUI_H
#define STATSUI_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "IObserver.h"

class Game;

class StatsUI : public GameState, public IObserver {
public:
    explicit StatsUI(Game& game);
    ~StatsUI() override;

    void handleEvent(sf::Event& event, Game& game) override;
    void update(Game& game) override;
    void render(sf::RenderWindow& window, Game& game) override;

    void onStatsUpdated(int gamesPlayed, int wins) override;

private:
    int      totalGames;
    int      totalWins;
    sf::Font font;
    std::optional<sf::Text> statsText;
};

#endif // STATSUI_H
