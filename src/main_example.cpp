#include <iostream>
#include "player.h"


int main() {
    Player player(2000);
    int bx = 0;
    int by = 0;
    int x =0;
    int y = 0;
    for(int i = 0; i < 100; i++) {
        Player::Direction move = player.move();
        switch(move) {
            case Player::UP:
                std::cout << "UP" << std::endl;
                y++;
                break;
            case Player::LEFT:
                std::cout << "LEFT" << std::endl;
                x--;
                break;
            case Player::DOWN:
                std::cout << "DOWN" << std::endl;
                y--;
                break;
            case Player::RIGHT:
                std::cout << "RIGHT" << std::endl;
                x++;
                break;
            case Player::SET_BM:
                std::cout << "BOOKMARK" << std::endl;
                bx = x;
                by = y;
                break;
        }
        x %= 4;
        y %= 5;
        if(x < 0) {x = 4 - x;}
        if(y < 0) {y = 5 - y;}
        if(x == bx && y == by && move != Player::SET_BM) {
            player.hitBookmark();
        }
    }
    return 0;
}