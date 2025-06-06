#ifndef IOBSERVER_H
#define IOBSERVER_H

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onStatsUpdated(int gamesPlayed, int wins) = 0;
};

#endif 