#ifndef MANAGERCPP_MAZE_H
#define MANAGERCPP_MAZE_H


#include <string>
#include <array>
#include <vector>

/*
 * Type for ordered pair. As a position in board, the first coordinate is the y-axis (between 0 to height - 1)
 * and the second one is the x-axis (between 0 the width - 1).
 */
typedef std::array<int, 2> ordered_pair;

class Maze {
    int max_steps;
    std::string maze_file, maze_name;
    std::string maze_description;
    ordered_pair dimensions{}, start{}, end{};
    int getInitLines(std::ifstream &fin);
public:
    enum Cell{PASS=0, WALL, END, OOB};
    Maze(std::string _maze_file, std::string _maze_name);
    Maze() = default;
    int loadMaze();
    Cell getCell(int i, int j);
    int getMaxSteps();
    ordered_pair getDimensions();
    ordered_pair getStart();
    ordered_pair getEnd();
private:
    std::vector<std::vector<Cell>> board;
};


#endif //MANAGERCPP_MAZE_H
