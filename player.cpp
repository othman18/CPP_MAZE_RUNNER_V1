//
//  Player.cpp
//  Ex2
//
//  Created by othman watad on 11.05.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include "player.h"

Cell& Player::getCurrentCell(){
    return *currentCell;
}

Move Player::changeDirection(){
    std::cout<<"player changed direction"<<std::endl;
    
//    int newMove = (prevMove + 1) % 4, numMoves=0;

    int newMove = (prevMove + 1) % 4, numMoves=0;


    Cell* tmp = currentCell;
    bool retry = true;
    while(retry && numMoves < 4){
        setPosition(tmp, (Move)newMove);
        if(tmp->status == Status::UNKNOWN){
            retry = false;
            continue;
        }
        setPosition(tmp, (Move)newMove, true);  //go back
        newMove = (newMove + 1) % 4;
        numMoves++;
    }
    if(numMoves < 4){
        prevMove = (Move)newMove;
        setPlayerPosition(prevMove);
        return prevMove;
    }

    BFS();
    makeStack(candidateCell);
    usingStack = true;
    Cell *target = myStack.top();
    myStack.pop();
    Move m = whichWay(target);
    setPlayerPosition(m);
    return m;
}

void Player::setBookmark(){
    cellToBookmark[currentCell] = bookmarks;
    bookmarkToCell[bookmarks]=currentCell;
    bookmarks++;
}

Cell& Player::getCellFromBM(int bm){
    return *bookmarkToCell[bm];
}

int Player::getBMFromCell(Cell* c){
    return cellToBookmark[c];
}

Move Player::move(){
    steps++;
    getCurrentCell().status = Status::VISITED;

    if(steps == 0){
        prevMove = Move::LEFT;
        currentCell->setBookMark();
        setPlayerPosition(SET_BM);
        setBookmark();
        return SET_BM;
    }
    
    if(isWall){
        isWall=false;
        return changeDirection();
    }
    
    if(usingStack){
        Cell* target = myStack.top();
        myStack.pop();
        if(myStack.empty()){
            usingStack = false;
            foundCandidate = false;
        }
        prevMove = whichWay(target);
        setPlayerPosition(prevMove);
        return prevMove;
    }
    
    if(!currentCell->hasBookmark()){
        currentCell->setBookMark();
        setPlayerPosition(SET_BM);
        setBookmark();
        return Move::SET_BM;
    }
    
    switch (prevMove) {
        case UP:
            if(currentCell->up && currentCell->up->status == Status::VISITED)
                return changeDirection();
            break;
        case DOWN:
            if(currentCell->down && currentCell->down->status == Status::VISITED)
                return changeDirection();
            break;
        case LEFT:
            if(currentCell->left && currentCell->left->status == Status::VISITED)
                return changeDirection();
            break;
        case RIGHT:
            if(currentCell->right && currentCell->right->status == Status::VISITED)
                return changeDirection();
            break;
        default:
            break;
    }
    setPlayerPosition(prevMove);
    return prevMove;
}

void Player::hitWall(){
    std::cout<<"hit Wall"<<std::endl;
    isWall=true;
    currentCell->status=Status::WALL;
    setPlayerPosition(prevMove,true);

}

void Player::hitBookmark(int seq){
    if(usingStack)
        return;
    std::cout<<"hit bookmark"<<std::endl;
    setPlayerPosition(prevMove, true);
    deletePointer(prevMove, seq);
    Cell::cellCount--;
    currentCell = &getCellFromBM(seq);
}

void Player::setPlayerPosition(Move move, bool reverse){
    setPosition(currentCell, move, reverse);
}

void Player::setPosition(Cell*& c, Move move, bool reverse){
    switch (move) {
        case Move::UP:
            c = reverse ? c->goDown() : c->goUp();
            break;
        case Move::DOWN:
            c = reverse ? c->goUp() : c->goDown();
            break;
        case Move::LEFT:
            c = reverse ? c->goRight() : c->goLeft();
            break;
        case Move::RIGHT:
            c = reverse ? c->goLeft() : c->goRight();
            break;
        default:
            break;
    }
}

void Player::deletePointer(Move move, int seq){
    Cell *tmp = &getCellFromBM(seq);
    switch (move) {
        case Move::UP:
            currentCell->up = nullptr;
            delete currentCell->up;
            tmp->down = currentCell;
            currentCell->up = &getCellFromBM(seq);
            break;
        case Move::DOWN:
            currentCell->down = nullptr;
            delete currentCell->down;
            tmp->up = currentCell;
            currentCell->down = &getCellFromBM(seq);
            break;
        case Move::LEFT:
            currentCell->left = nullptr;
            delete currentCell->left;
            tmp->right = currentCell;
            currentCell->left = &getCellFromBM(seq);
            break;
        case Move::RIGHT:
            currentCell->right = nullptr;
            delete currentCell->right;
            tmp->left = currentCell;
            currentCell->right = &getCellFromBM(seq);
            break;
        default:
            break;
    }
}

std::string Player::moveString(Move move){
    std::string moves[] = {"left","down","right","up","BM"};
    return moves[(int)move];
}

void Player::BFS(){
    BFSVersion++;
    std::cout<<"BFS #"<<BFSVersion<<std::endl;
    std::queue<Cell*> q;
    q.push(currentCell);
    Cell* current, *tmp;
    while(!foundCandidate && !q.empty()){
        current = q.front();
        q.pop();
        tmp = current;
        
        if(current->getVersion() == BFSVersion)  // already checked
            continue;
        current->setVersion(BFSVersion);
        if(current->status == Status::WALL)  //stop at walls
            continue;
        if(current->status == Status::VISITED){
            for(Move m: {LEFT, DOWN, RIGHT, UP}){
                setPosition(tmp, m);
               
                if(tmp->getVersion() == BFSVersion){  // already checked
                    setPosition(tmp, m, true);  //go back
                    continue;
                }
                tmp->prev = current;
                q.push(tmp);
                setPosition(tmp, m, true);
            }
            continue;
        }
        foundCandidate = true;
        candidateCell = current;
    }
}

void Player::makeStack(Cell* c){
    //create a stack that will contain the player's path to the closest unknow cell
    myStack.push(c);

    while(c->cellID != currentCell->cellID){
        
        myStack.push(c->prev);
        c = c->prev;
    }
    myStack.pop();  //CHECK AGAIN !!!! pop this to avoid same coordinates at start
}

Move Player::whichWay(Cell* target){
    
    if(currentCell->up->cellID == target->cellID){
        return UP;
    }else if(currentCell->down->cellID == target->cellID){
        return DOWN;
    }else if(currentCell->left->cellID == target->cellID){
        return LEFT;
    }else if(currentCell->right->cellID == target->cellID){
        return RIGHT;
    }
    std::cout<<"error at whichWay"<<std::endl;
    return SET_BM;  //this is an error
}
