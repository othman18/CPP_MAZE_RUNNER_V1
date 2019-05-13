//
//  cell.cpp
//  Ex2
//
//  Created by othman watad on 11.05.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include "cell.h"

int Cell::cellCount;

bool Cell::hasBookmark(){
    return this->bookmarked;
}

void Cell::setBookMark(){
    this->bookmarked = true;
}

Cell* Cell::goUp(){
    if(!this->up){  //upper cell is not defined
        up = new Cell();
    }
    up->down = this;
    return up;
}

Cell* Cell::goDown(){
    if(!this->down){  //upper cell is not defined
        down = new Cell();
    }
    down->up = this;
    return down;
}

Cell* Cell::goLeft(){
    if(!this->left){  //upper cell is not defined
        left = new Cell();
    }
    left->right = this;
    return left;
}

Cell* Cell::goRight(){
    if(!this->right){  //upper cell is not defined
        right = new Cell();
    }
    right->left = this;
    return right;
}

int Cell::getVersion(){
    return BFSversion;
}

void Cell::setVersion(int v){
    BFSversion = v;
}
