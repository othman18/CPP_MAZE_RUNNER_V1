//
// Created by noamt on 4/5/19.
//

#include "player.h"
#include "playerUtils.h"
#include <iostream>


Player::Player(int max_steps): max_steps(max_steps){
    x = 0;
    y = 0;
    bm_x = 0;
    bm_y = 0;
    tmp_steps = 0;
    total_steps = 0;
    circle_num = 0;
    is_wall = false;
    is_bookmark = false;
    direction = UP;
    tmp_direction = UP;
}


Player::Direction Player::move() {
    if(total_steps == 0) {
        total_steps++;
        return SET_BM;
    }
    if(is_wall) {
        chooseDirection();
        nextPosition(x, y, direction);
        maze[{x, y}] = PASS;
        return direction;
    }
    handleMove();
    return direction;
}


void Player::hitWall() {
    maze[{x, y}] = WALL;
    prevPosition(x, y, direction);
    is_wall = true;
}

void Player::hitBookmark() {
    bm_x = x;
    bm_y = y;
    is_bookmark = true;
}

void Player::handleMove() {
    if(tmp_steps == 4 * circle_num) {
        circle_num += 2;
        tmp_steps = -1;
    } else if(tmp_steps == 0) {
        tmp_steps = 0;
        setBookmark();
    } else if(tmp_steps % circle_num == 0 || tmp_steps == 1) {
        direction = (Direction) ((direction + 1) % 4);
    }
    nextPosition(x, y, direction);
    tmp_steps++;
    total_steps++;
}


void Player::setBookmark() {
    bm_x = x;
    bm_y = y;
    direction = SET_BM;
}

void Player::chooseDirection() {
    std::vector<Direction > new_options;
    std::vector<Direction > old_options;
    for(Direction d: {UP, LEFT, DOWN, RIGHT}) {
        int tmp_x = x, tmp_y = y;
        nextPosition(tmp_x, tmp_y, d);
        Pair n = {tmp_x, tmp_y};
        if(maze[n] == UNKNOWN) {
            new_options.push_back(d);
        } else if(maze[n] == PASS) {
            old_options.push_back(d);
        }
    }
    if(new_options.empty()) {
        new_options = old_options;
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, new_options.size() - 1);
    direction = new_options[dist(rng)];
}