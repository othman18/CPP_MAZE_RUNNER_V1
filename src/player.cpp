//
// Created by noamt on 4/5/19.
//

#include "player.h"
#include "playerUtils.h"



Player::Player(int max_steps): max_steps(max_steps){
    x = 0;
    y = 0;
    dim_x = 0;
    dim_y = 0;
    tmp_steps = 0;
    total_steps = 0;
    circle_num = 0;
    bm_x = 0;
    bm_y = 0;
    find_x = 0;
    find_y = 0;
    is_wall = false;
    is_bookmark = false;
    knows_x = false;
    knows_y = false;
    direction = UP;
}


Player::Direction Player::move() {
    if(total_steps == 0) {
        total_steps++;
        return SET_BM;
    }

    handleLastMove();
    handleMove();
    return direction;
}


void Player::hitWall() {
    if(is_wall) {
        return;
    }
    maze[{x, y}] = WALL;
    int tmp_x = x;
    int tmp_y = y;
    Direction dir = direction;
    if (tmp_steps == 4 * circle_num) {
        dir = (Direction) ((dir + 1) % 4);
    }
    nextPosition(tmp_x, tmp_y, dir);
    is_wall = true;
}


void Player::hitBookmark() {
    is_bookmark = true;
}


void Player::handleLastMove() {
    if(is_wall) {
        is_wall = false;
    }
    else if(is_bookmark) {
        is_bookmark = false;
    }
    else {
        maze[{x, y}] = PASS;
    }
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
    direction = SET_BM;
    bm_x = x;
    bm_y = y;
    maze[{x, y}] = BM;
}


void Player::findPath() {
}