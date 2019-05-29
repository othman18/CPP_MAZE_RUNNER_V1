#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Maze.h"

Maze::Maze(std::string _maze_file, std::string _maze_name){
    maze_file = std::move(_maze_file);
    maze_name = _maze_name;
    max_steps = 0;
    dimensions = {0, 0};
    start = {-1, -1};
    end = {-1, -1};
}

int commonError(std::ifstream &fin) {
    fin.close();
    return 1;
}

int badHeader(std::ifstream &fin, const std::string &line, int line_number, const char *param) {
    std::cout << "Bad maze file header:" << std::endl;
    std::cout << "expected in line " << line_number << " - " << param << " = <num>" << std::endl;
    std::cout << "got: " << line << std::endl;
    fin.close();
    return 1;
}

int badMazeFile(std::ifstream &fin, const std::string &msg) {
    std::cout << "Bad maze in maze file: " << std::endl;
    std::cout << msg << std::endl;
    return commonError(fin);
}

int getSpecialLine(const char *param, std::string &line) {
    // Remove any spaces
    std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
    line.erase(end_pos, line.end());
    end_pos = std::remove(line.begin(), line.end(), '\r');
    line.erase(end_pos, line.end());

    if (count(line.begin(), line.end(), '=') != 1)
        return -1;

    // Verify that there is exactly 1 "=" sign, and split the line by this sign.
    size_t equal_sign = line.find('=');
    // Check if the left value is the expected flag.
    if (line.substr(0, equal_sign) != param)
        return -1;

    // Get the right value (after the "=" sign"), and convert to integer.
    std::string suffix = line.substr(equal_sign + 1, line.size() - equal_sign - 1);
    int value;
    std::stringstream(suffix) >> value;
    if (value <= 0)
        return -1;
    return value;
}

int Maze::getInitLines(std::ifstream &fin) {
    // Get first line (maze description).
    std::string line;
    if (!getline(fin, line)) {
        std::cout << "Empty maze file " << maze_file << std::endl;
        return commonError(fin);
    }
    maze_description = line;

    // Check for MaxSteps, Rows, and Cols.
    if (!getline(fin, line))
        return badHeader(fin, "", 2, "MaxSteps");
    max_steps = getSpecialLine("MaxSteps", line);
    if (max_steps <= 0)
        return badHeader(fin, line, 2, "MaxSteps");

    if (!getline(fin, line))
        return badHeader(fin, "", 3, "Rows");
    dimensions[0] = getSpecialLine("Rows", line);
    if (dimensions[0] <= 0)
        return badHeader(fin, line, 3, "Rows");

    if (!getline(fin, line))
        return badHeader(fin, "", 4, "Cols");
    dimensions[1] = getSpecialLine("Cols", line);
    if (dimensions[1] <= 0)
        return badHeader(fin, line, 4, "Cols");

    return 0;
}

int Maze::loadMaze() {
    std::ifstream fin(maze_file);
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    // Get the first lines (header).
    int err = getInitLines(fin);
    if (err > 0)
        return err;

    int height = dimensions[0];
    int width = dimensions[1];

    // Set the board to be a matrix of size <height> rows and <width> columns.
    for (int i = 0; i < height; i++) {
        board.emplace_back();
        for (int j = 0; j < width; j++)
            board[i].push_back(PASS);
    }

    int i = 0;
    std::string line;
    while (getline(fin, line) && i < height) {
        int line_size = line.size();
        for (int j = 0; j < width && j < line_size; j++) {
            // Check the current symbol in current line.
            char c = line[j];
            switch (c) {
                case ' ':
                    board[i][j] = PASS;
                    break;
                case '#':
                    board[i][j] = WALL;
                    break;
                case '@':
                    // Check if start was already set.
                    if (start[0] >= 0)
                        return badMazeFile(fin, "More than one @ in maze");
                    // Set start.
                    start = {i, j};
                    break;
                case '$':
                    // Check if end was already set.
                    if (end[0] >= 0)
                        return badMazeFile(fin, "More than one $ in maze");
                    // Set end.
                    end = {i, j};
                    board[i][j] = END;
                    break;
                default:
                    // Unknown symbol.
                    std::cout << "Bad maze file:" << std::endl;
                    std::string chr = c == '\t' ? "TAB" : std::to_string(c);
                    std::cout << "Wrong character in maze: " << chr << " in row " << i << ", col " << j << std::endl;
                    fin.close();
                    return 1;
            }
        }
        i++;
    }
    // Check if there wasn't any start or end symbols at all.
    if (start[0] < 0)
        return badMazeFile(fin, "Missing @ in maze");
    if (end[0] < 0)
        return badMazeFile(fin, "Missing $ in maze");
    fin.close();
    return 0;
}

// Get the cell value in the given position. If position is out of bounds, it will return OOB.
Maze::Cell Maze::getCell(int i, int j) {
    if (i < 0 || j < 0 || i >= dimensions[0] || j >= dimensions[1])
        return OOB;
    return board[i][j];
}

// Getter for max steps.
int Maze::getMaxSteps() {
    return max_steps;
}

// Getter for board dimensions. First coordinate is the board height, and second one is board width.
ordered_pair Maze::getDimensions() {
    return dimensions;
}

// Getter for maze start position.
ordered_pair Maze::getStart() {
    return start;
}

// Getter for maze end position.
ordered_pair Maze::getEnd() {
    return end;
}
