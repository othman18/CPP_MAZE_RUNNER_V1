#ifndef MANAGERCPP_MATCHMANAGER_H
#define MANAGERCPP_MATCHMANAGER_H


#include <string>
#include <map>
#include <stack>
#include <functional>
#include <memory>
#include "Maze.h"
#include "AbstractAlgorithm.h"

class MatchManager {
    std::string mazes_path, algorithm_path, output_path;
    int num_threads, numMatches;
    std::map<std::string, std::string> maze_files;
    std::map<std::string, std::string> algorithm_files;
    std::map<std::string, Maze> mazes;
    std::map<std::string, std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithms;
    std::vector<void *> handlers;
    static int playGame(MatchManager *manager, std::string maze_name, std::string algorithm_name);
    static void playThread(MatchManager *manager);
    static int getFilesAndNames(std::string &path, std::map<std::string, std::string> &files, std::string type);
    void setResults(std::string, std::string, int);
    std::map<std::string,std::map<std::string,int>> matchResults;
    std::vector<std::string> availablePlayers;
    std::map<std::string, std::vector<std::string>> mazesLeft;
    int findMaxLen();
    void printResults(std::map<std::string, std::map<std::string, int>> &results, int max_result);
public:
    MatchManager(std::string mazes_path, std::string algorithm_path, std::string output_path, int num_threads);
    int loadAll();
    void threadedPlayAll();
};


#endif //MANAGERCPP_MATCHMANAGER_H
