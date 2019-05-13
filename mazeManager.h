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
    int width, height, actual_x, actual_y;
    char** mazeMatrix;
    Pair start{}, end{};
    std::map<Pair,int> coordinatesBookmarks;
public:
    MazeManager(Extractor* extractor, Player* player);
    bool manageMaze();
    void setManagerPosition(int& x, int& y, Move direction, bool reverse=false);
    bool isBookmarkHere();
    void setBookmark(int);
    int getBookmark();
};


#endif //CPP_EX1_MAZEMANAGER_H
