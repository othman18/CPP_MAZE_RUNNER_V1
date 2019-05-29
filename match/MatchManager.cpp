#include <utility>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <dlfcn.h>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <fstream>
#include "MatchManager.h"
#include "AlgorithmSaver.h"

std::mutex matchResultMutex, availablePlayersMutex, myMutex;


std::once_flag flag1;

MatchManager::MatchManager(std::string m_path, std::string a_path, std::string o_path, int n_threads) {
    mazes_path = std::move(m_path);
    algorithm_path = std::move(a_path);
    output_path = std::move(o_path);
    num_threads = n_threads;
}

/*
 * Get all the files and their names in the given path that ends with the given extension type.
 * The parameter files is a map where a full file path points the absolute file name (without the extension).
 * The function will go over the files in the given directory.
 * For every file that ends with the given extension, the function will add an entry to files,
 * where the key is the full file path, and the value is the absolute file name.
 * On success, the function will return 0.
 * On one of the 2 following cases of failure, the function will print an error message and reutnr -1:
 *     1. The given directory does not exist.
 *     2. There aren't any files in the given directory that have the given extension.
 */
int MatchManager::getFilesAndNames(std::string &path, std::map<std::string, std::string> &files, std::string type) {
    // Check if directory exists.
    if (!std::filesystem::is_directory(path)) {
        std::cout << "Given parameter " << path << " is not a directory" << std::endl;
        return -1;
    }

    bool has_files = false;
    for (auto &entry : std::filesystem::directory_iterator(path)) {
        auto &filepath = entry.path();
        if (filepath.extension().string() == type) {
            // filepath.string() is the full file path, and filepath.filename().string() is the absolute file name.
            std::string filepath_string = filepath.string();
            files[filepath_string] = filepath.filename().string();
            has_files = true;
        }
    }

    // Check if didn't found any files.
    if (!has_files) {
        std::cout << "There are no files in path " << path << " with extension " << type << std::endl;
        return -1;
    }
    return 0;
}

/*
 * Load both mazes and algorithms from the given path.
 * At the beginning, for both mazes and algorithms, the function will get all the relevant files.
 * For each maze file: the function will create an instance of Maze and try to load the maze from the file.
 * For each algorithm file: the function will dynamically load the .so file and save the current function that
 * was loaded by AlgorithmRegistration. Since we can't change the header of AbstractAlgorithm, the functions will be
 * saved in a map where the algorithm name (the file name) will point the function. We don't need to call the functions
 * since we will call each one of the functions several times during the run of playAll.
 * The function will always save the handle of the .so file (return value of dlopen) in a map where the file name
 * points the handler, so we can close all the handlers at the end of the program.
 * On success the function will return 0.
 * On one of the 3 following cases of failure, the function will print an error message and return -1:
 *     1. Getting maze files or algorithm files failed.
 *     2. Loading one of the mazes failed.
 *     3. Loading one of the algorithms failed.
 */
int MatchManager::loadAll() {
    /*
     * TODO: fix bugs in this function. Most of them are probably because wrong use in STD data structures
     *  and variables by reference.
     */
    if (getFilesAndNames(mazes_path, maze_files, ".maze") < 0)
        return -1;

    if (getFilesAndNames(algorithm_path, algorithm_files, ".so") < 0)
        return -1;

    for (auto &entry : maze_files) {
        mazes[entry.second] = Maze(entry.first, entry.second);
        if (mazes[entry.second].loadMaze() != 0)
            return -1;
    }

    for (auto &entry :algorithm_files) {
        char *chars = new char[entry.first.length()];
        for (int i = 0; i < (int) entry.first.length(); i++)
            chars[i] = entry.first[i];
        chars[entry.first.length()] = '\0';
        void *handler = dlopen(chars, RTLD_LAZY);
        if (!handler) {
            std::cout << "Failed to dynamically load file " << entry.first << std::endl;
            return -1;
        }
        delete[] chars;

        std::function<std::unique_ptr<AbstractAlgorithm>()> function = AlgorithmSaver::getFunction();
        handlers.push_back(handler);
        algorithms[entry.second] = function;
    }
    return 0;
}


/*
 * Play a single game: a single algorithm on a single maze.
 */
int MatchManager::playGame(MatchManager *manager, std::string maze_name, std::string algorithm_name) {
    Maze &maze = manager->mazes[maze_name];
    std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm_function = manager->algorithms[algorithm_name];
    std::unique_ptr<AbstractAlgorithm> _algorithm = algorithm_function();
    std::string output_path = manager->output_path;
    bool generate_output = output_path.length() > 0;
    int max_steps = maze.getMaxSteps();
    ordered_pair start = maze.getStart();
    ordered_pair dimensions = maze.getDimensions();
    int height = dimensions[0];
    int width = dimensions[1];
    int steps = 0;
    ordered_pair pos = start;
    std::map<ordered_pair, int> bookmarks;
    int bookmarks_num = 1;
    std::string output;
    std::map<AbstractAlgorithm::Move, std::string> move_map = {{AbstractAlgorithm::LEFT,     "L"},
                                                               {AbstractAlgorithm::UP,       "U"},
                                                               {AbstractAlgorithm::DOWN,     "D"},
                                                               {AbstractAlgorithm::RIGHT,    "R"},
                                                               {AbstractAlgorithm::BOOKMARK, "B"}};

    while (steps < max_steps) {
        steps++;
        AbstractAlgorithm::Move move = _algorithm->move();
        ordered_pair original_pos = pos;
        if (move == AbstractAlgorithm::LEFT) { pos[1]--; }
        else if (move == AbstractAlgorithm::RIGHT) { pos[1]++; }
        else if (move == AbstractAlgorithm::DOWN) { pos[0]--; }
        else if (move == AbstractAlgorithm::UP) { pos[0]++; }
        else if (move == AbstractAlgorithm::BOOKMARK) { bookmarks[pos] = bookmarks_num++; }

        if (generate_output)
            output.append(move_map[move] + "\n");
        pos[0] = pos[0] < 0 ? height + pos[0] : pos[0] % height;
        pos[1] = pos[1] < 0 ? width + pos[1] : pos[1] % width;
        Maze::Cell cell = maze.getCell(pos[0], pos[1]);
        if (cell == Maze::WALL) {
            _algorithm->hitWall();
            pos = original_pos;
        } else if (cell == Maze::END)
            break;
        else if (move != AbstractAlgorithm::BOOKMARK && bookmarks.count(pos) > 0)
            _algorithm->hitBookmark(bookmarks[pos]);
        if(steps == max_steps) {
            steps = -1;
            break;
        }
    }

    if(!generate_output)
        return steps;

    output.append(steps > 0 ? "X\n" : "!\n");
    std::string output_file = output_path;
    output_file.append("/");
    output_file.append(maze_name);
    output_file.append(algorithm_name);
    output_file.append(".output");

    std::ofstream fout;
    fout.open(output_file);
    if (!fout.is_open()) {
        std::cout << "Failed to write output to file " << output_file << std::endl;
        return 1;
    }

    fout << output;
    fout.close();
    return steps;
}

void MatchManager::setResults(std::string alg, std::string maze, int result) {
    std::lock_guard<std::mutex> lock(matchResultMutex);
    matchResults[alg][maze] = result;
}

void MatchManager::playThread(MatchManager *manager) {
    std::unique_lock<std::mutex> lock(availablePlayersMutex, std::defer_lock);
    std::unique_lock<std::mutex> lock_numMatches(myMutex, std::defer_lock);

    while (manager->numMatches != 0) {
        lock.lock();
        if (manager->numMatches == 0) {
            lock.unlock();  // in case a thread was waiting and there were no more matches left, release all the threads
            return;
        }

        if (manager->availablePlayers.size() == 0 && manager->numMatches != 0) {
            lock.unlock();
            continue;  //busy waiting, threads waiting for the next player to finish running his current maze
        }

        std::string player = manager->availablePlayers.front();  //get the next player in line
        manager->availablePlayers.erase(manager->availablePlayers.begin());

        std::string maze = manager->mazesLeft[player].front();  //get the next maze that the player hasn't ran yet
        manager->mazesLeft[player].erase(manager->mazesLeft[player].begin());
        lock.unlock();  //allow the next thread to access the next player and maze

        int result = playGame(manager, maze, player);
        manager->setResults(player, maze, result);

        lock_numMatches.lock();  //lock the condition that allows the threads to stay in the loop, and make sure not to add players that ran all the mazes
        manager->numMatches--;
        if (manager->mazesLeft[player].size() != 0) {
            manager->availablePlayers.push_back(player);
        }
        lock_numMatches.unlock();
    }
}


void MatchManager::threadedPlayAll() {
    // Create a stack of string pairs. The first item in a pair will be the maze name,
    // and the second one will be the algorithm name.

    for (auto &algorithm_entry : algorithms) {
        availablePlayers.push_back(algorithm_entry.first);
        for (auto &maze_entry : mazes) {
            mazesLeft[algorithm_entry.first].push_back(maze_entry.first);
        }
    }

    numMatches =(int) (algorithms.size() * mazes.size());
    std::vector<std::thread> threads(num_threads);
    for (int i = 0; i < num_threads; i++)
        threads.emplace_back(playThread, this);

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    int max_result = -1;
    for(auto &algorithm_entry : algorithms) {
        for(auto &maze_entry : mazes) {
            if(matchResults[algorithm_entry.first][maze_entry.first] > max_result)
                max_result = matchResults[algorithm_entry.first][maze_entry.first];
        }
    }
    printResults(matchResults, max_result);

}

int MatchManager::findMaxLen() {
    int max_len = 0;
    for (auto &maze_entry: mazes) {
        std::string maze_name = maze_entry.first;
        if ((int) maze_name.length() > max_len) {
            max_len = maze_name.length();
        }
    }

    for (auto &algorithm_entry: algorithms) {
        std::string algorithm_name = algorithm_entry.first;
        if ((int) algorithm_name.length() > max_len) {
            max_len = algorithm_name.length();
        }
    }
    return max_len;
}

void printWithSpaces(std::string str, int max_len) {
    std::cout << str << std::flush;
    for (int i = 0; i < max_len - (int) str.length(); i++) {
        std::cout << ' ' << std::flush;
    }
}

void MatchManager::printResults(std::map<std::string, std::map<std::string, int>> &results, int max_result) {
    int max_len = findMaxLen();
    int max_result_len = std::to_string(max_result).length();
    if (max_result_len > max_len)
        max_len = max_result_len;

    std::string special_line;
    for (int i = 0; i < (int)(max_len * (mazes.size() + 1) + mazes.size()); i++)
        special_line.append("-");

    std::cout << special_line << std::endl;
    std::cout << '|' << std::flush;
    for (int i = 0; i < max_len; i++)
        std::cout << ' ' << std::flush;
    std::cout << '|' << std::flush;

    for (auto &maze_entry: mazes) {
        std::string maze_name = maze_entry.first;
        printWithSpaces(maze_name, max_len);
        std::cout << '|' << std::flush;
    }
    std::cout << std::endl;
    std::cout << special_line << std::endl;

    for (auto &algorithm_entry: algorithms) {
        std::string algorithm_name = algorithm_entry.first;
        std::cout << '|' << std::flush;
        printWithSpaces(algorithm_name, max_len);
        std::cout << '|' << std::flush;
        auto &current_results = results[algorithm_name];
        for (auto &maze_entry: mazes) {
            std::string maze_name = maze_entry.first;
            printWithSpaces(std::to_string(current_results[maze_name]), max_len);
            std::cout << '|' << std::flush;
        }
        std::cout << std::endl;
        std::cout << special_line << std::endl;
    }
}
