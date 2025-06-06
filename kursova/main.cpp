#include "Game.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        // In case any texture/font fails
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}