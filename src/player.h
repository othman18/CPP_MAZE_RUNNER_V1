//
// Created by noamt on 4/5/19.
//

#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include <array>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <random>

typedef std::array<int, 2> Pair;


class Player {
    enum Cell{UNKNOWN=0, PASS=1, WALL=2};
    const int max_steps;
    int x, y, bm_x, bm_y, tmp_steps, total_steps, circle_num;
    bool is_wall, is_bookmark;
    std::map<Pair, Cell> maze;
public:
    explicit Player(int max_steps);
    enum Direction{UP=0, LEFT=1, DOWN=2, RIGHT=3, SET_BM=4};
    Direction move();
    void hitWall();
    void hitBookmark();
private:
    Direction direction, tmp_direction;
    std::stack<Direction> path;
    void handleMove();
    void setBookmark();
    void chooseDirection();
};


#endif //EX1_PLAYER_H
