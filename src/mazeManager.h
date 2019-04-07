//
// Created by noamt on 4/7/19.
//

#ifndef CPP_EX1_MAZEMANAGER_H
#define CPP_EX1_MAZEMANAGER_H

#include "extractMaze.h"
#include "player.h"


class MazeManager {
    Extractor* extractor;
    Player* player;
    int width, height, max_steps;
    char** mazeMatrix;
    Pair start{}, end{};
public:
    MazeManager(Extractor* extractor, Player* player);
    bool manageMaze();
};


#endif //CPP_EX1_MAZEMANAGER_H
