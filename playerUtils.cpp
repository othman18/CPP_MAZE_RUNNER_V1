//
// Created by noamt on 4/6/19.
//

#include "playerUtils.h"
#include "player.h"
#include <vector>


void setPosition(int& x, int& y, Player::Direction direction, bool backwards=false) {
    int sign = backwards ? -1 : 1;
    switch(direction) {
        case Player::UP:
            y += sign;
            break;
        case Player::LEFT:
            x -= sign;
            break;
        case Player::DOWN:
            y -= sign;
            break;
        case Player::RIGHT:
            x += sign;
            break;
        default:
            break;
    }
}


void nextPosition(int& x, int& y, Player::Direction direction) {
    setPosition(x, y, direction, false);
}

void prevPosition(int& x, int& y, Player::Direction direction) {
    return setPosition(x, y, direction, true);
}