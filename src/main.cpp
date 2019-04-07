//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//

#include "extractMaze.h"
#include "player.h"
<<<<<<< HEAD:src/main.cpp
#include "playerUtils.h"
=======
#include "mazeManager.h"


>>>>>>> 1cd5d882ddef58a6bbe65e08e7863848c48728da:main.cpp
int main(int argc, char *argv[]) {
    if (argc < 3){
        if (argc == 2){
            std::cout <<"Missing maze file argument in command line"<<std::endl;
        } else if (argc == 1){
            std::cout <<"Missing output file argument in command line" <<std::endl;
        }
        return 0;
    }
    const std::string inputPath = argv[1], outputPath = argv[2];

    Extractor ex;
    ex.readFile(inputPath);

    Player player(ex.getMaxSteps());
    MazeManager manager(&ex, &player);
    std::cout << manager.manageMaze() << std::endl;
    return 0;
    ex.writeFile(outputPath);

    if (ex.everyThingIsOkay)
        std::cout<<"finished successfuly, player obj can run"<<std::endl;
    else
        std::cout<<"something went wrong, don't run the player obj"<<std::endl;

    return 0;
}
