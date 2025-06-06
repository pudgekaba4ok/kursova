#include "Game.h"
#include "MainMenuState.h"
#include "InGameState.h"
#include "PauseState.h"
#include "StatsUI.h"
#include "SettingsManager.h"
#include "AssetManager.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({ 1280, 720 }), "Minesweeper"),
    ongoingGame(false),
    currentDifficulty(LevelFactory::Difficulty::Easy)
{
    AssetManager::getInstance().loadTexture("cell_hidden", "Images/cell_hidden.png");
    AssetManager::getInstance().loadTexture("cell_revealed", "Images/num_0.png");
    AssetManager::getInstance().loadTexture("cell_flagged", "Images/cell_flagged.png");
    AssetManager::getInstance().loadTexture("mine", "Images/mine.png");
    AssetManager::getInstance().loadTexture("num_0", "Images/num_0.png");
    AssetManager::getInstance().loadTexture("num_1", "Images/num_1.png");
    AssetManager::getInstance().loadTexture("num_2", "Images/num_2.png");
    AssetManager::getInstance().loadTexture("num_3", "Images/num_3.png");
    AssetManager::getInstance().loadTexture("num_4", "Images/num_4.png");
    AssetManager::getInstance().loadTexture("num_5", "Images/num_5.png");
    AssetManager::getInstance().loadTexture("num_6", "Images/num_6.png");
    AssetManager::getInstance().loadTexture("num_7", "Images/num_7.png");
    AssetManager::getInstance().loadTexture("num_8", "Images/num_8.png");
    if (!m_font.openFromFile("fonts/arialmt.ttf")) {
        throw std::runtime_error("Font loading failed");
    }
    SettingsManager::getInstance().loadSettings();

    initStates();
    changeState(StateID::MainMenu);
}

void Game::initStates() {
    stateMap[StateID::MainMenu] = std::make_unique<MainMenuState>(*this);
    stateMap[StateID::InGame] = std::make_unique<InGameState>(*this);
    stateMap[StateID::Pause] = std::make_unique<PauseState>(*this);
    stateMap[StateID::StatsUI] = std::make_unique<StatsUI>(*this);
    stateMap[StateID::SettingsUI] = std::make_unique<SettingsManager::SettingsState>(*this);
}

Game::~Game()
{
    while (!stateStack.empty()) {
        stateStack.pop(); // No delete needed, stateMap owns the states
    }
}

void Game::run()
{
    while (window.isOpen()) {
        while (const std::optional <sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
            if (!stateStack.empty()) {
                sf::Event ev = *event;
                stateStack.top()->handleEvent(ev, *this);
            }
        }

        if (!stateStack.empty()) {
            stateStack.top()->update(*this);
            stateStack.top()->render(window, *this);
        }
    }
}

void Game::changeState(StateID newState)
{
    while (!stateStack.empty()) {
        stateStack.pop();
    }

    auto it = stateMap.find(newState);
    if (it != stateMap.end()) {
        stateStack.push(it->second.get());
    }
}

void Game::pushState(StateID newState)
{
    auto it = stateMap.find(newState);
    if (it != stateMap.end()) {
        stateStack.push(it->second.get());
    }
}

void Game::popState()
{
    if (!stateStack.empty()) {
        stateStack.pop();
    }
}

bool Game::hasOngoingGame() const
{
    return ongoingGame;
}

void Game::startNewGame() {
    ongoingGame = true;

    auto inGameState = dynamic_cast<InGameState*>(stateMap[StateID::InGame].get());
    if (inGameState) {
        Field* newField = LevelFactory::createField(currentDifficulty);
        inGameState->setField(newField);
    }

    changeState(StateID::InGame);
}

void Game::continueGame()
{
    if (ongoingGame) {
        changeState(StateID::InGame);
    }
}

void Game::showStats()
{
    pushState(StateID::StatsUI);
}

void Game::showSettings()
{
    pushState(StateID::SettingsUI);
}

void Game::exitGame()
{
    window.close();
}

void Game::resumeGame()
{
    popState();

    if (!stateStack.empty()) {
        if (auto inGame = dynamic_cast<InGameState*>(stateStack.top())) {
            inGame->resume(*this);
        }
    }
}
