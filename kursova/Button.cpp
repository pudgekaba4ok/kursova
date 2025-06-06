#include "Button.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Button::Button(const sf::Vector2f& position,
    const sf::Vector2f& size,
    std::unique_ptr<Command> cmd,
    sf::Font& font,
    std::optional<sf::Text> label)
    : m_label(std::move(label)),
    box(size),
    command(std::move(cmd)),
    enabled(true),
    font(font)
{
   
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color(200, 200, 200));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);

    
    if (m_label) {
        m_label->setFont(font);
        m_label->setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = m_label->getLocalBounds();

        m_label->setOrigin({
            textBounds.position.x + textBounds.size.x / 2.0f,
            textBounds.position.y + textBounds.size.y / 2.0f
            });

        m_label->setPosition({
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f
            });
    }
}

void Button::draw(sf::RenderWindow& window) {
    box.setFillColor(enabled ? sf::Color(200, 200, 200) : sf::Color(150, 150, 150));

    window.draw(box);
    if (m_label) {
        window.draw(*m_label);
    }
}

void Button::handleEvent(const sf::Event& event, Game& game) {
    if (this == nullptr || !enabled) return;

    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseButton) {
            sf::Vector2f mousePos(
                static_cast<float>(mouseButton->position.x),
                static_cast<float>(mouseButton->position.y)
            );

            if (box.getGlobalBounds().contains(mousePos))
            {
                command->execute(game);
            }
        }
    }
}

void Button::setEnabled(bool en) {
    enabled = en;
}

bool Button::isEnabled() const {
    return enabled;
}