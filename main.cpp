//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//

#include "mazeManager.h"

int main(int argc, char *argv[]) {
//    if (argc < 3){
//        if (argc == 2){
//            std::cout <<"Missing maze file argument in command line"<<std::endl;
//        } else if (argc == 1){
//            std::cout <<"Missing output file argument in command line" <<std::endl;
//        }
//        return 0;
//    }
//    const std::string inputPath =argv[1];
//    const std::string outputPath =argv[2];

    if (argc < 3 && argv[0])
        std::cout<<"start"<<std::endl; //delete

    const std::string inputPath = "/Users/othman/Desktop/TAU/TAU_UNI/cpp/Ex2/Ex2/mazes/wide_recursive_maze.txt";
    const std::string outputPath ="/Users/othman/Desktop/TAU/TAU_UNI/cpp/Ex2/Ex2/mazes/out.txt";

    Extractor ex;
    ex.readFile(inputPath);
    ex.writeFile(outputPath);

    if (ex.everyThingIsOkay){
        std::cout<<"player can run"<<std::endl;
        Player player;
        MazeManager manager(&ex, &player);
        manager.manageMaze();
    }
//    else
//        std::cout<<"something went wrong, don't run the player obj"<<std::endl;
    return 0;
}
