//
// Created by noamt on 4/7/19.
//

#include "mazeManager.h"
#include <iostream>


MazeManager::MazeManager(Extractor *ex, Player* pl): extractor(ex), player(pl) {
    width = extractor->getWidth();
    height = extractor->getHeight();
    start = extractor->getStart();
    end = extractor->getEnd();
    mazeMatrix = extractor->getMazeMatrix();
}


bool MazeManager::manageMaze() {
    Move move;
    actual_x = start[0];
    actual_y = start[1];
    int maxCounter = 2000;
    char cell = '_';
    
    while(cell != '$'  && player->steps <= maxCounter){
        move = player->move();
        std::cout<<"move #"<<player->steps <<" = "<<player->moveString(move)<<std::endl;

        setManagerPosition(actual_x, actual_y, move);
        
        actual_x = actual_x < 0 ? width + actual_x : actual_x % width;
        actual_y = actual_y < 0 ? height + actual_y : actual_y % height;
        cell = mazeMatrix[actual_x][actual_y];
        
        
        if(move != Move::SET_BM || player->steps == 0){
            std::cout<<"currently at: ("<<actual_x<<", "<<actual_y;
            std::cout<<") cell id:"<<player->getCurrentCell().cellID;
            std::cout<<" "<<player->getCurrentCell().status<<std::endl;
            
        }
        if(cell == '#') {
            player->hitWall();
            setManagerPosition(actual_x, actual_y, move,true);
            //incase the coordinates are negative

            std::cout<<"go back to: ("<<actual_x<<", "<<actual_y;
            std::cout<<") cell id:"<<player->getCurrentCell().cellID<<std::endl;
        }else if(cell == '$'){
            std::cout<<"player found $"<<std::endl;
            break;
        }else{
            if(move == Move::SET_BM){
                setBookmark(player->bookmarks-1);
            }else if(move != Move::SET_BM ){
                if(isBookmarkHere()){
                    player->hitBookmark(getBookmark());
                    std::cout<<"teleported to: "<<actual_x<<", "<<actual_y<<std::endl;
                    std::cout<<"cell id:"<<player->getCurrentCell().cellID<<std::endl;
                }
            }
        }
        std::cout<<std::endl;
    }
    return cell == '$';
}


void MazeManager::setManagerPosition(int& x, int& y, Move direction, bool reverse){
    int sign = reverse ? -1 : 1;
    switch(direction) {
        case Move::UP:
            y -= sign;
            break;
        case Move::LEFT:
            x -= sign;
            break;
        case Move::DOWN:
            y += sign;
            break;
        case Move::RIGHT:
            x += sign;
            break;
        default:
            break;
    }
}


bool MazeManager::isBookmarkHere(){
    return coordinatesBookmarks.count({actual_x,actual_y})==1;
}

void MazeManager::setBookmark(int bmID){
    coordinatesBookmarks[{actual_x,actual_y}] = bmID;
}

int MazeManager::getBookmark(){
    return  coordinatesBookmarks[{actual_x,actual_y}];
}
