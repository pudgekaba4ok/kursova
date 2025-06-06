#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class Game; 


class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvent(sf::Event& event, Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(sf::RenderWindow& window, Game& game) = 0;
};

#endif // GAMESTATE_H