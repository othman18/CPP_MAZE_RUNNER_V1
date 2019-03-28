//
//  extractMaze.h
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//
#include <iostream>
#ifndef extractMaze_h
#define extractMaze_h
class Extractor{
    const int MAX_STEPS=0;
    const int NUM_ROWS=0;
    const int NUM_COLS=0;
    int** mazeMatrix;
public:
    Extractor(int steps, int row, int cols):MAX_STEPS(steps),NUM_ROWS(row),NUM_COLS(cols){
        mazeMatrix = new int*[NUM_ROWS];
        for(int i=0; i<NUM_ROWS;i++){
            mazeMatrix[i] = new int[NUM_COLS];
        }
        std::cout<<"created maze"<<std::endl;
    }
    ~Extractor(){
        std::cout<<"deleting maze"<<std::endl;
        for(int i=0;i<NUM_ROWS;i++){
            delete[] mazeMatrix[i];
        }
        delete [] mazeMatrix;
//        mazeMatrix = nullptr;                         //should I leave this out?
        std::cout<<"deleted maze"<<std::endl;
    }
};

#endif /* extractMaze_h */
