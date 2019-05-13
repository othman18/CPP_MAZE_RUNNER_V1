//
//  cell.hpp
//  Ex2
//
//  Created by othman watad on 11.05.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#ifndef cell_hpp
#define cell_hpp

enum Status{UNKNOWN=0, VISITED, WALL};

class Cell{
    bool bookmarked=false;
    int BFSversion=0;
    
public:
    Cell* up=nullptr, *right=nullptr, *down=nullptr, *left=nullptr, *prev=nullptr;
    int cellID=0;
    Status status;
    static int cellCount;
    
    Cell(){
        if(!cellCount)
            cellCount = 0;
        cellCount++;
        cellID = cellCount;
        status = UNKNOWN;
    }
    ~Cell(){
        delete up;
        delete down;
        delete left;
        delete right;
    }
    bool hasBookmark();
    void setBookMark();
    Cell* goDown();
    Cell* goUp();
    Cell* goLeft();
    Cell* goRight();
    int getVersion();
    void setVersion(int);
};

#endif /* cell_hpp */
