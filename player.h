//
//  Player.hpp
//  Ex2
//
//  Created by othman watad on 11.05.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <map>
#include <stack>
#include "queue"
#include "cell.h"

//enum Move{LEFT=0, DOWN, RIGHT, UP, SET_BM};
enum Move{LEFT=0, UP, RIGHT, DOWN, SET_BM};

class Player{
    Cell* currentCell=nullptr, *candidateCell=nullptr;
    std::map<Cell*, int> cellToBookmark;  //int is the bookmark id
    std::map<int, Cell*> bookmarkToCell;
    Move prevMove;
    bool isWall=false, foundCandidate=false;
    std::stack<Cell*> myStack;
    
public:
    int steps=-1, bookmarks=1, BFSVersion=0;
    bool usingStack=false;
    std::string moveString(Move);
    Player(){currentCell = new Cell();}
    Move move();
    void hitWall();
    void hitBookmark(int);

    Cell& getCurrentCell();
    void setPlayerPosition(Move, bool reverse=false);
    void setPosition(Cell*&, Move, bool reverse=false);
    
    void setBookmark();
    Cell& getCellFromBM(int);
    int getBMFromCell(Cell*);

    void deletePointer(Move, int);
    Move changeDirection();
    
    void BFS();
    void makeStack(Cell*);
    Move whichWay(Cell* );

};


#endif /* Player_hpp */
