A project which implements the use of shared objects and dynamic memory in c++.

Given a set of players and mazes, the players have to navigate through the mazes and find the target without exceeding the max number of steps that each of them has.

The players are blind to the structure and dimensions of the maze.

./match -maze_path <maze_path> -algorithm_path <algorithms_path> -output <output_path> -num_threads <#threads>

if no output path was given, then the result will only be printed and not saved
default number of threads is 1
