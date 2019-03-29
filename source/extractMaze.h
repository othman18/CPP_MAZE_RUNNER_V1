//
//  extractMaze.h
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//
#include <iostream>
#include <fstream>

#ifndef extractMaze_h
#define extractMaze_h
class Extractor{
    const int* MAX_STEPS;
    const int* NUM_ROWS;
    const int* NUM_COLS;
    int** mazeMatrix=nullptr;
public:
    ~Extractor(){
        if(!mazeMatrix)
            return;
        
        for(int i=0;i<*NUM_ROWS;i++){
            delete[] mazeMatrix[i];
            mazeMatrix[i] = nullptr;    //should I leave this out?
        }
        delete [] mazeMatrix;
        mazeMatrix = nullptr;   //should I leave this out?
        std::cout<<"deleted maze-matrix"<<std::endl;
    }
    void checkForValidInput();
    void readFile(const std::string& filename);
    void writeFile(const std::string& filename);
    void createMaze(int steps, int row, int cols);
};

#endif /* extractMaze_h */
