#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Cell.h"

class Game {
public:
    std::vector<std::vector<Cell>> grid;

    Game();
    void randomize();
    void reset();
    void update();
    int countAliveNeighbors(int x, int y);
    void draw();
};

#endif
