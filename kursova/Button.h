#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>    
#include <memory>
#include <string>
#include <optional>
#include "Command.h"            

class Game;

class Button {
public:
    Button(const sf::Vector2f& position,
           const sf::Vector2f& size,
           std::unique_ptr<Command> cmd,  
           sf::Font& font,
           std::optional<sf::Text> label = std::nullopt);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, Game& game);
    void setEnabled(bool enabled);
    bool isEnabled() const;

private:
    std::optional<sf::Text> m_label;
    sf::RectangleShape box;
    std::unique_ptr<Command> command;
    bool enabled;
    sf::Font& font;  
};

#endif 