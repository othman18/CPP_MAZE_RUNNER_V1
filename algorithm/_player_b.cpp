//
// Created by noamt on 5/28/19.
//

#include "AlgorithmRegistration.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <random>


typedef std::array<int, 2> pair;

class _player_b : public AbstractAlgorithm {
    enum Cell {
        PASS, WALL
    };
    pair position{0, 0}, original_position{0, 0};
    bool random_mode = false;
    std::map<pair, Cell> board;
    std::map<int , pair> bookmarks;
    int bookmarks_num = 0, width = 0, height = 0;
    Move current_move;
    std::stack<Move> path;

    pair _calculatePath(std::map<pair, pair> &tree) {
        std::set<pair> current_nodes = {position};
        std::set<pair> next_nodes;
        while (!current_nodes.empty()) {
            next_nodes.clear();
            for (pair node : current_nodes) {
                std::vector<pair> directions = {{position[0] - 1, position[1]},
                                                {position[0] + 1, position[1]},
                                                {position[0],     position[1] - 1},
                                                {position[0],     position[1] + 1}};
                for (auto &direction : directions) {
                    if (board.count(direction) == 0) {
                        tree[direction] = node;
                        return direction;
                    }
                    if (board[direction] == PASS && tree.count(direction) == 0) {
                        next_nodes.insert(direction);
                        tree[direction] = node;
                    }
                }
            }
            current_nodes = next_nodes;
        }
        tree.clear();
        return {0, 0};
    }

    bool calculatePath() {
        std::map<pair, pair> tree;
        pair target = _calculatePath(tree);
        if(tree.empty())
            return false;
        while(target != position) {
//            std::cout << "{ " << target[0] << ", " << target[1] << " }" << std::endl;
            pair parent = tree[target];
            if(target[0] == parent[0] - 1 && target[1] == parent[1]) {path.push(UP);}
            else if (target[0] == parent[0] + 1 && target[1] == parent[1]) {path.push(DOWN);}
            else if (target[0] == parent[0] && target[1] == parent[1] - 1) {path.push(LEFT);}
            else {path.push(RIGHT);}
            target = parent;
        }
        path.push(BOOKMARK);
        return true;
    }

public:
    Move move() override {
        if (!random_mode && path.empty() && !calculatePath())
            random_mode = true;
        if (random_mode) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, 4);
            return (Move)dist(rng);
        }
        original_position = position;
        current_move = path.top();
        path.pop();
        if(current_move == UP)
            position[0]--;
        else if (current_move == DOWN)
            position[0]++;
        else if(current_move == LEFT)
            position[1]--;
        else if (current_move == RIGHT)
            position[1]++;
        else
            bookmarks[++bookmarks_num] = position;
        board[position] = PASS;
        return current_move;
    }

    void hitWall() override {
        board[position] = WALL;
        position = original_position;
    }

    void hitBookmark(int seq) override {
        pair bookmark_point = bookmarks[seq];
        if(board.count(bookmark_point) > 0)
            return;
        if (current_move == UP || current_move == DOWN)
            width = std::abs(position[0] - bookmark_point[0]);
        else if(current_move == LEFT || current_move == RIGHT)
            width = std::abs(position[1] - bookmark_point[1]);
    }
};

REGISTER_ALGORITHM(_player_b)
