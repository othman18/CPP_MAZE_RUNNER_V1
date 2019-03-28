//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include <iostream>
#include "extractMaze.h"

int main() {
    Extractor* ex = new Extractor(10,1,2);
    ex->mazeMatrix[0][0] = 1;
    ex->mazeMatrix[0][1] = 2;
    delete ex;
    std::cout <<"done"<<std::endl;
    return 0;
}
