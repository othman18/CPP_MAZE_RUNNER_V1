//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include "extractMaze.h"

int main(int argc, char *argv[] ) {
    if (argc < 3){
        if (argc == 2){
            std::cout <<"Missing maze file argument in command line"<<std::endl;
        } else if (argc == 1){
            std::cout <<"Missing output file argument in command line" <<std::endl;
        }
        return 0;
    }
    const std::string inputPath = argv[1], outputPath = argv[2];
    Extractor* ex = new Extractor();
    
    ex->readFile("/Users/othman/Downloads/recursive_bug_maze.txt");

    
    
    delete ex;
    if (ex->everyThingOkay)
        std::cout<<"finished successfuly"<<std::endl;
    else
        std::cout<<"something went wrong"<<std::endl;
    
    return 0;
}
