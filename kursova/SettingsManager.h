#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class SettingsManager {
public:
    static SettingsManager& getInstance();

    void loadSettings();
    void saveSettings();

    void setVolume(int v);
    int getVolume() const;
    void setCellStyle(int idx);
    int getCellStyle() const;

    class SettingsState : public GameState {
    public:
        SettingsState(Game& game);
        ~SettingsState() override = default;

        void handleEvent(sf::Event& event, Game& game) override;
        void update(Game& game) override;
        void render(sf::RenderWindow& window, Game& game) override;

    private:
        sf::Font font;
        std::optional<sf::Text>  headerText;
        std::optional<sf::Text>  volumeText;
        std::optional<sf::Text> styleText;

    };

private:
    SettingsManager();
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    int volume;
    int cellStyle;
};

#endif // SETTINGSMANAGER_H
