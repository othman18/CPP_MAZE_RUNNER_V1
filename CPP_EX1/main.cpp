//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#include <iostream>
#include "extractMaze.h"

int main() {
    extractor* ex = new extractor(10,1,1);
    ex->mazeMatrix[0][0] = 1;
    ex->mazeMatrix[1][1] = 1;
    std::cout << sizeof(ex->mazeMatrix)<<std::endl;
    return 0;
}

