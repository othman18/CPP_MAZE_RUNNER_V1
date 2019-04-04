//
//  extractMaze.h
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#ifndef extractMaze_h
#define extractMaze_h

#include <iostream>
#include <fstream>
#include <sys/stat.h>
class Extractor{
    int NUM_ROWS;  // change to const..
    int NUM_COLS;  // change to const..
    int MAX_STEPS;  // change to const..
    char** mazeMatrix=nullptr;
public:
    bool everyThingIsOkay = true;  // used for debugging
    ~Extractor(){
        if(!mazeMatrix){
            std::cout<<"nothing to delete"<<std::endl;
            return;
        }
        for(int i=0;i<NUM_COLS;i++){
            delete[] mazeMatrix[i];
            mazeMatrix[i] = nullptr;   //should I leave this out?
        }
        delete [] mazeMatrix;
        mazeMatrix = nullptr;   //should I leave this out?
        std::cout<<"deleted maze-matrix"<<std::endl;
    }
    void readFile(const std::string& fileName);
    void writeFile(const std::string& fileName);
    void createMaze();
    bool checkLine(std::string line, std::string compareWith, int lineNum);
    void printMAze();
};

void mazeInputError(const std::string line, int lineNum);
bool is_number(const std::string& s);
bool checkWordSpaces(std::string line);
bool fileExists(const std::string& name);
#endif /* extractMaze_h */
