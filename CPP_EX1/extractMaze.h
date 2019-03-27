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
class extractor{
    const int MAX_STEPS;
    const int NUM_ROWS;
    const int NUM_COLS;
public:
    int** mazeMatrix;
    extractor(int steps, int row, int cols):MAX_STEPS(steps),NUM_ROWS(row),NUM_COLS(cols){
        mazeMatrix = new int*[NUM_ROWS];
        for(int i=0; i<NUM_ROWS;i++){
            mazeMatrix[i] = new int[NUM_COLS];
        }
        std::cout<<"created maze"<<std::endl;
    }
    ~extractor(){
        std::cout<<"deleting maze"<<std::endl;
        for(int i=0;i<NUM_ROWS;i++){
            delete[] mazeMatrix[i];
        }
        delete [] mazeMatrix;
        std::cout<<"deleted maze"<<std::endl;
    }
};

#endif /* extractMaze_h */
