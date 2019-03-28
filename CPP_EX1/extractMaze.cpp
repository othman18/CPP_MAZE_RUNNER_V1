//
//  extractMaze.cpp
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include "extractMaze.h"

void Extractor::checkForValidInput(){

}

void Extractor::createMaze(int steps, int row, int cols){
    MAX_STEPS=&steps;
    NUM_ROWS=&row;
    NUM_COLS=&cols;
    mazeMatrix = new int*[*NUM_ROWS];
    for(int i=0; i<*NUM_ROWS;i++){
        mazeMatrix[i] = new int[*NUM_COLS];
    }
    std::cout<<"created maze-matrix"<<std::endl;
}


void Extractor::readFile(const std::string& fileName){
    std::string line;
    std::ifstream fin(fileName);
    if (fin.is_open())
    {
        while ( std::getline(fin, line) )
        {
            std::cout << line << '\n';
        }
        fin.close();
    }
    else std::cout <<"Command line argument for maze: "<< fileName <<" doesn't lead to a maze file or leads to a file that cannot be opened"<<std::endl;
};
