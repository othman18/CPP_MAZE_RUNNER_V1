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
    tmp_direction = UP;
}


Player::Direction Player::move() {
    if(total_steps == 0) {
        total_steps++;
        return SET_BM;
    }
    if(is_wall) {
        if(x == find_x && y == find_y) {
            is_wall = false;
            direction = tmp_direction;
        }
        else {
            direction = path.top();
            path.pop();
            nextPosition(x, y, direction);
            total_steps++;
            return direction;
        }
    }
    handleMove();
    return direction;
}


void Player::hitWall() {
    if(tmp_steps == 4 * circle_num) {
        return;
    }
    maze[{x, y}] = WALL;
    if(!is_wall) {
        tmp_direction = direction;
    }
    if (tmp_steps % circle_num == 0) {
        tmp_direction = (Direction) ((tmp_direction + 1) % 4);
    }
    find_x = x;
    find_y = y;
    nextPosition(find_x, find_y, tmp_direction);
    prevPosition(x, y, direction);
    findPath();
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
    Pair src = {x, y};
    Pair dst = {find_x, find_x};
    Pair current = src;
    std::vector<Pair> all_neighbors;
    std::set<Pair> neighbors = {src};
    std::set<Pair> next_neighbors;
    std::map<Pair, Pair*> tree;
    while(true) {
        for(Pair item: neighbors) {
            Pair nearby[4] = {{item[0] + 1, item[1]}, {item[0] - 1, item[1]}, {item[0], item[1] + 1}, {item[0], item[1] - 1}};
            for(Pair neighbor: nearby) {
                if (neighbor == src || (maze[neighbor] == PASS && tree[neighbor] != nullptr)) {
                    all_neighbors.push_back(item);
                    next_neighbors.insert(neighbor);
                    tree[neighbor] = &(all_neighbors[all_neighbors.size() - 1]);
                    if (neighbor == dst) {
                        path.empty();
                        while(neighbor != src) {
                            Pair parent = *tree[neighbor];
                            if(neighbor[0] < parent[0]) {
                                path.push(RIGHT);
                            } else if(neighbor[0] > parent[0]) {
                                path.push(LEFT);
                            } else if(neighbor[1] < parent[1]) {
                                path.push(UP);
                            } else {
                                path.push(DOWN);
                            }
                            neighbor = parent;
                        }
                        return;
                    }
                }
            }
            neighbors.clear();
            neighbors.merge(next_neighbors);
            next_neighbors.clear();
        }
    }
}