//
//  Created by othman watad on 11.05.19.
//
#include "AlgorithmRegistration.h"
#include <iostream>
#include <map>
#include <stack>
#include <queue>


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
    if(!this->down){  //lower cell is not defined
        down = new Cell();
    }
    down->up = this;
    return down;
}

Cell* Cell::goLeft(){
    if(!this->left){  //lef cell is not defined
        left = new Cell();
    }
    left->right = this;
    return left;
}

Cell* Cell::goRight(){
    if(!this->right){  //right cell is not defined
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
class _player_a : public AbstractAlgorithm {
    int steps=-1, bookmarks=1, BFSVersion=0;
    bool usingStack=false;
    Cell* currentCell=nullptr, *candidateCell=nullptr;
    std::map<Cell*, int> cellToBookmark;  //int is the bookmark id
    std::map<int, Cell*> bookmarkToCell;
    AbstractAlgorithm::Move prevMove;
    bool isWall=false, foundCandidate=false;
    std::stack<Cell*> myStack;

    AbstractAlgorithm::Move changeDirection(){
        //std::cout<<"player changed direction"<<std::endl;

        int newMove = (prevMove + 1) % 4, numMoves=0;
		Cell* tmp = currentCell;
        bool retry = true;
        while(retry && numMoves < 4){
  	              
	    setPosition(tmp, (AbstractAlgorithm::Move)newMove, false);
            if(tmp->status == Status::UNKNOWN){
                retry = false;
                continue;
            }
            setPosition(tmp, (AbstractAlgorithm::Move)newMove, true);  //go back
            newMove = (newMove + 1) % 4;
            numMoves++;
        }
        if(numMoves < 4){
	    prevMove = (AbstractAlgorithm::Move)newMove;
            setPlayerPosition(prevMove, false);
            return prevMove;
        }

        BFS();
        makeStack(candidateCell);
        usingStack = true;
        Cell *target = myStack.top();
        myStack.pop();
        AbstractAlgorithm::Move m = whichWay(target);
        setPlayerPosition(m,false);
        return m;
    }

    Cell &getCurrentCell() {
        return *currentCell;
    }

    void setBookmark(){
        cellToBookmark[currentCell] = bookmarks;
        bookmarkToCell[bookmarks]=currentCell;
        bookmarks++;
    }

    Cell& getCellFromBM(int bm){
        return *bookmarkToCell[bm];
    }

    int getBMFromCell(Cell* c){
        return cellToBookmark[c];
    }

    void setPlayerPosition(AbstractAlgorithm::Move move, bool reverse){
        setPosition(currentCell, move, reverse);

    }

    void setPosition(Cell*& c, AbstractAlgorithm::Move move, bool reverse){
        switch (move) {
            case AbstractAlgorithm::Move::UP:
                c = reverse ? c->goDown() : c->goUp();
                break;
            case AbstractAlgorithm::Move::DOWN:
                c = reverse ? c->goUp() : c->goDown();
                break;
            case AbstractAlgorithm::Move::LEFT:
                c = reverse ? c->goRight() : c->goLeft();
                break;
            case AbstractAlgorithm::Move::RIGHT:
                c = reverse ? c->goLeft() : c->goRight();
                break;
            default:
                break;
        }
    }

    void deletePointer(AbstractAlgorithm::Move move, int seq){
        Cell *tmp = &getCellFromBM(seq);
        switch (move) {
            case AbstractAlgorithm::Move::UP:
                currentCell->up = nullptr;
                delete currentCell->up;
                tmp->down = currentCell;
                currentCell->up = &getCellFromBM(seq);
                break;
            case AbstractAlgorithm::Move::DOWN:
                currentCell->down = nullptr;
                delete currentCell->down;
                tmp->up = currentCell;
                currentCell->down = &getCellFromBM(seq);
                break;
            case AbstractAlgorithm::Move::LEFT:
                currentCell->left = nullptr;
                delete currentCell->left;
                tmp->right = currentCell;
                currentCell->left = &getCellFromBM(seq);
                break;
            case AbstractAlgorithm::Move::RIGHT:
                currentCell->right = nullptr;
                delete currentCell->right;
                tmp->left = currentCell;
                currentCell->right = &getCellFromBM(seq);
                break;
            default:
                break;
        }
    }

    void BFS(){
        BFSVersion++;
        //std::cout<<"BFS #"<<BFSVersion<<std::endl;
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
                for(AbstractAlgorithm::Move m: {LEFT, DOWN, RIGHT, UP}){
                    setPosition(tmp, m, false);

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

    std::string moveString(AbstractAlgorithm::Move move){
        std::string moves[] = {"left","down","right","up","BM"};
        return moves[(int)move];
    }

    AbstractAlgorithm::Move whichWay(Cell* target){

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
        return AbstractAlgorithm::Move::BOOKMARK;  //this is an error
    }

    void makeStack(Cell* c){
        //create a stack that will contain the player's path to the closest unknow cell
        myStack.push(c);

        while(c->cellID != currentCell->cellID){

            myStack.push(c->prev);
            c = c->prev;
        }
        myStack.pop();  //CHECK AGAIN !!!! pop this to avoid same coordinates at start
    }

public:
    Move move(){
	
	if(steps==-1){
		currentCell=new Cell();
	}
        steps++;
        getCurrentCell().status = Status::VISITED;


        if(steps == 0){
            prevMove = AbstractAlgorithm::Move::LEFT;
            currentCell->setBookMark();
            setPlayerPosition(AbstractAlgorithm::Move::BOOKMARK,false);
            setBookmark();
            return AbstractAlgorithm::Move::BOOKMARK;
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
            setPlayerPosition(prevMove,false);
            return prevMove;
        }


        if(!currentCell->hasBookmark()){

          currentCell->setBookMark();
            setPlayerPosition(AbstractAlgorithm::Move::BOOKMARK,false);
            setBookmark();
            return AbstractAlgorithm::Move::BOOKMARK;
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
			std::cout<<"stuck"<<std::endl;
                break;
        }
        setPlayerPosition(prevMove,false);
        return prevMove;
    }

    void hitWall(){
        isWall=true;
        currentCell->status=Status::WALL;
        setPlayerPosition(prevMove,true);

    }

    void hitBookmark(int seq){

        if(usingStack){
            return;
	}

        //std::cout<<"hit bookmark"<<std::endl;
        setPlayerPosition(prevMove, true);
        deletePointer(prevMove, seq);
        Cell::cellCount--;

	currentCell = &getCellFromBM(seq);
    }

};

REGISTER_ALGORITHM(_player_a)


