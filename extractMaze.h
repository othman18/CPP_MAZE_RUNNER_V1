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
#include <algorithm>
//#include <filesystem>
#include <array>
#include <queue>


typedef std::array<int, 2> Pair;


class Extractor{
    int NUM_ROWS;
    int NUM_COLS;
    int MAX_STEPS;
    char** mazeMatrix=nullptr;
    Pair start;
    Pair end;
    bool headerError = false, mazeError = false;
public:
    bool everyThingIsOkay = true;
    
    ~Extractor(){
        if(!mazeMatrix){
//            std::cout<<"nothing to delete"<<std::endl;
            return;
        }
        for(int i=0;i<NUM_COLS;i++){
            delete[] mazeMatrix[i];
            mazeMatrix[i] = nullptr;
        }
        delete [] mazeMatrix;
        mazeMatrix = nullptr;  
//        std::cout<<"deleted maze-matrix"<<std::endl;
    }
    void readFile(const std::string& fileName);
    void writeFile(const std::string& fileName);
    void writeMoveToFile(const std::string& fileNam);
    void createMaze();
    bool checkLine(std::string line, std::string compareWith, int lineNum);
    void printMaze();
    char getCell(int i, int j);
    int getMaxSteps();
    int getWidth();
    int getHeight();
    Pair getStart();
    Pair getEnd();
    char** getMazeMatrix();
    void mazeInputError(const std::string line, int lineNum);
};

bool is_number(const std::string& s);
bool checkWordSpaces(std::string line);
bool fileExists(const std::string& name);


#endif /* extractMaze_h */
