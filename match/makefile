COMP = g++-8.3.0

OBJS = main.o AlgorithmRegistration.o AlgorithmSaver.o MatchManager.o Maze.o
EXEC = match
CPP_COMP_FLAG = -std=c++17  -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -ldl -export-dynamic -lstdc++fs -pthread #(-rdynamic)

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@

main.o: main.cpp MatchManager.o
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmSaver.o
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Maze.o: Maze.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $.*cpp

MatchManager.o: MatchManager.cpp AlgorithmSaver.o Maze.o
	$(COMP) $(CPP_COMP_FLAG) -c $.*cpp

AlgorithmSaver.o: AlgorithmSaver.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $.*cpp

clean:
	rm -f $(OBJS) $(EXEC)
