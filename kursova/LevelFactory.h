#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include "Field.h"

class LevelFactory {
public:
    enum class Difficulty { Easy, Medium, Hard };
    static Field* createField(Difficulty diff);
};

#endif // LEVELFACTORY_H