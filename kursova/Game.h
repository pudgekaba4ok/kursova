#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "GameState.h"
#include "StatsManager.h"
#include "SettingsManager.h"
#include "LevelFactory.h"
#include "AssetManager.h"
#include "MainMenuState.h"
#include "InGameState.h"
#include <SFML/OpenGL.hpp>

class Game {
public:
    enum class StateID { MainMenu, InGame, Pause, StatsUI, SettingsUI, currentState, previousState };

    Game();
    ~Game();

    void run();


    void changeState(StateID newState);
    void pushState(StateID newState);
    void popState();

    bool hasOngoingGame() const;
    void startNewGame();
    void continueGame();
    void showStats();
    void showSettings();
    void exitGame();
    void resumeGame(); 

    LevelFactory::Difficulty getSelectedDifficulty() const { return currentDifficulty; }
    void setSelectedDifficulty(LevelFactory::Difficulty diff) { currentDifficulty = diff; }

    sf::RenderWindow& getWindow() { return window; }
    sf::Font& getFont() { return m_font; }

    void setOngoingGame(bool val) { ongoingGame = val; }
private:
    sf::Font m_font;
    sf::RenderWindow window;
    std::stack<GameState*> stateStack;
    bool ongoingGame;
    LevelFactory::Difficulty currentDifficulty;
    std::map<StateID, std::unique_ptr<GameState>> stateMap;

    void initStates();
};

#endif // GAME_H