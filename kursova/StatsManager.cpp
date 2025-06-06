#include "StatsManager.h"

StatsManager& StatsManager::getInstance() {
    static StatsManager instance;
    return instance;
}

void StatsManager::attach(IObserver* obs) {
    observers.push_back(obs);
}

void StatsManager::detach(IObserver* obs) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), obs),
        observers.end());
}

void StatsManager::recordGameResult(bool victory) {
    ++gamesPlayed;
    if (victory) ++wins;
    notify();
}

void StatsManager::notify() {
    for (auto* obs : observers) {
        obs->onStatsUpdated(gamesPlayed, wins);
    }
}