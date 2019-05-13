COMP = g++-8#.3.0
#put all your object files here
OBJS = main.o extractMaze.o player.o mazeManager.o cell.o


CPP_LINK_FLAG = -lstdc++fs


#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies

extractMaze.o: extractMaze.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 

player.o: player.cpp cell.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

cell.o: cell.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

mazeManager.o: mazeManager.cpp extractMaze.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp


main.o: main.cpp mazeManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
