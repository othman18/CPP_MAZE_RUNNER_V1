#include <iostream>
#include <string>
#include <dlfcn.h>
#include "MatchManager.h"


/*
 * Parse a string to positive int.
 * The method will go over the string and validate that all the characters are valid digits of a
 * positive integer ('0'-'9'), and also calculate the value.
 * On success, the function will return the calculated value.
 * On one of the 2 following cases of failure, the function will print an error message and return -1:
 *     1. The calculate number is 0.
 *     2. The string contains a character which is out of the range of '0'-'9'.
 */
int parsePositiveInt(std::string &arg) {
    int value = 0;
    for (const char &c : arg) {
        if ('0' <= c && c <= '9')
            // The value of (c - '0') contains the integer value of c (i.e. '7'-->7).
            value = value * 10 + c - '0';
        else {
            std::cout << "Invalid value for parameter -num_threads: should be given a positive integer" << std::endl;
            return -1;
        }
    }
    if (value == 0) {
        std::cout << "Invalid value for parameter -num_threads: should be given a positive integer" << std::endl;
        return -1;
    }
    return value;
}

/*
 * Parse command line flags for the program.
 * Getting argc and argv as arguments, and they should be the given arguments to main function.
 * The function should change mazes_path, algorithm_path, output_path, and num_threads to the correct values
 * according to the command line arguments.
 * If any parameter wasn't given, it stays as it was defined before.
 * If a parameter was given without any value (i.e. "... -mazes_path -algorithm_path") it will ignore this
 * parameter and won't change its value.
 * If a parameter is set twice it will take the last value.
 * On success, the function will return 0.
 * In one of the 2 following cases of failure, the function will print an error message and return -1:
 *     1. Invalid parameter flag (i.e. "-mmazes_path", or "mazes_path" (without "-")).
 *     2. The given value for -num_threads is non a valid and positive number.
 */
int parseFlag(int argc, char **argv, std::string &mazes_path, std::string &algorithm_path, std::string &output_path,
              int &num_threads) {
    if (argc == 1) {
        std::cout << "Missing parameter: -num_threads" << std::endl;
        return -1;
    }
    std::string current_flag = argv[1];
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            current_flag = arg;
            continue;
        }
        if (current_flag == "-maze_path")
            mazes_path = arg;
        else if (current_flag == "-algorithm_path")
            algorithm_path = arg;
        else if (current_flag == "-output")
            output_path = arg;
        else if (current_flag == "-num_threads") {
            if ((num_threads = parsePositiveInt(arg)) < 0)
                return -1;
        } else {
            std::cout << "Invalid parameter: " << current_flag << std::endl;
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    // Default path for mazes and algorithms is current path. Default number of threads is 1.
    std::string mazes_path("./"), algorithm_path("./"), output_path;
    int num_threads = 1;

    // Parse command line arguments. If parsing failed, exit the program.
    if (parseFlag(argc, argv, mazes_path, algorithm_path, output_path, num_threads) < 0)
        return 0;

    std::vector<void *> handlers;
    // Load mazes and algorithms from files. If loading failed, exit the program.
    MatchManager manager(mazes_path, algorithm_path, output_path, num_threads);
    if (manager.loadAll() < 0)
        return 0;

    // Play all the mazes with all the algorithms.
	manager.threadedPlayAll();
    for(void *handler : handlers)
        dlclose(handler);
	
    return 0;
}
