#include "LevelFactory.h"

Field* LevelFactory::createField(Difficulty diff) {
    constexpr int winW = 1280;
    constexpr int winH = 720;

    switch (diff) {
    case Difficulty::Easy:
        return new Field(9, 9, 10, 60, winW, winH);      
    case Difficulty::Medium:
        return new Field(16, 16, 40, 40, winW, winH);    
    case Difficulty::Hard:
        return new Field(30, 16, 99, 30, winW, winH);    
    default:
        return new Field(9, 9, 10, 60, winW, winH);
    }
}