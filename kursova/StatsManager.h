#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <vector>
#include "IObserver.h"

class StatsManager {
public:
    static StatsManager& getInstance();

    void attach(IObserver* obs);
    void detach(IObserver* obs);

    void recordGameResult(bool victory);

    int getGamesPlayed() const { return gamesPlayed; }
    int getWins() const { return wins; }

private:
    StatsManager() : gamesPlayed(0), wins(0) {}
    StatsManager(const StatsManager&) = delete;
    StatsManager& operator=(const StatsManager&) = delete;

    std::vector<IObserver*> observers;
    int gamesPlayed;
    int wins;

    void notify();
};

#endif // STATSMANAGER_H