#include "SettingsManager.h"
#include "Game.h"
#include <fstream>

SettingsManager& SettingsManager::getInstance() {
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager()
    : volume(50), cellStyle(0)
{
}

void SettingsManager::loadSettings() {
    std::ifstream in("settings.cfg");
    if (!in.is_open()) return;
    in >> volume >> cellStyle;
    in.close();
}

void SettingsManager::saveSettings() {
    std::ofstream out("settings.cfg");
    out << volume << " " << cellStyle;
    out.close();
}

void SettingsManager::setVolume(int v) {
    volume = std::max(0, std::min(100, v));

}

int SettingsManager::getVolume() const {
    return volume;
}

void SettingsManager::setCellStyle(int idx) {
    cellStyle = std::max(0, idx);
}

int SettingsManager::getCellStyle() const {
    return cellStyle;
}

SettingsManager::SettingsState::SettingsState(Game& game)
	: font(), headerText(), volumeText(), styleText()
    {
    if (!font.openFromFile("fonts/arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }
    headerText.emplace(font, "Settings (ESC to go back)", 20);
    headerText->setCharacterSize(20);
    headerText->setFillColor(sf::Color::White);
    headerText->setPosition({ 50.f, 50.f });

    volumeText.emplace(font, "Volume: ", 18);
    volumeText->setCharacterSize(18);
    volumeText->setFillColor(sf::Color::White);
    volumeText->setPosition({ 50.f, 120.f });

    styleText.emplace(font, "Cell Style: ", 18);
    styleText->setCharacterSize(18);
    styleText->setFillColor(sf::Color::White);
    styleText->setPosition({50.f, 180.f});

 
    volumeText->setString("Volume: " + std::to_string(SettingsManager::getInstance().getVolume()));
    styleText->setString("Cell Style: " + std::to_string(SettingsManager::getInstance().getCellStyle()));
}

void SettingsManager::SettingsState::handleEvent(sf::Event& event, Game& game) {
   if (event.is<sf::Event::KeyPressed>()) {
       const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
       if (keyEvent->code == sf::Keyboard::Key::Escape) {
           SettingsManager::getInstance().saveSettings();
           game.popState();
       }
       else if (keyEvent->code == sf::Keyboard::Key::Up) {
           int vol = SettingsManager::getInstance().getVolume();
           SettingsManager::getInstance().setVolume(vol + 5);
           volumeText->setString("Volume: " + std::to_string(SettingsManager::getInstance().getVolume()));
       }
       else if (keyEvent->code == sf::Keyboard::Key::Down) {
           int vol = SettingsManager::getInstance().getVolume();
           SettingsManager::getInstance().setVolume(vol - 5);
           volumeText->setString("Volume: " + std::to_string(SettingsManager::getInstance().getVolume()));
       }
       else if (keyEvent->code == sf::Keyboard::Key::Right) {
           int st = SettingsManager::getInstance().getCellStyle();
           SettingsManager::getInstance().setCellStyle(st + 1);
           styleText->setString("Cell Style: " + std::to_string(SettingsManager::getInstance().getCellStyle()));
       }
       else if (keyEvent->code == sf::Keyboard::Key::Left) {
           int st = SettingsManager::getInstance().getCellStyle();
           SettingsManager::getInstance().setCellStyle(std::max(0, st - 1));
           styleText->setString("Cell Style: " + std::to_string(SettingsManager::getInstance().getCellStyle()));
       }
   }
}

void SettingsManager::SettingsState::update(Game& game) {

}

void SettingsManager::SettingsState::render(sf::RenderWindow& window, Game& game) {
    window.clear(sf::Color(30, 30, 30));
    window.draw(*headerText);
    window.draw(*volumeText);
    window.draw(*styleText);
    window.display();
}