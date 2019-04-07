COMP = g++-8#5.3.0
#put all your object files here
<<<<<<< HEAD:src/makefile
OBJS = main.o extractMaze.o player.o playerUtils.o	#objects should be placed here! 
=======
OBJS = main.o extractMaze.o player.o playerUtils.o mazeManager.o	#objects should be placed here!

>>>>>>> 1cd5d882ddef58a6bbe65e08e7863848c48728da:makefile

CPP_LINK_FLAG = -lstdc++fs

#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies

extractMaze.o: extractMaze.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 

player.o:player.cpp playerUtils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

<<<<<<< HEAD:src/makefile
playerUtils.o: playerUtils.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

main.o: main.cpp extractMaze.h player.h playerUtils.h	#put dependencies here!
=======
playerUtils.o: playerUtils.cpp player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

mazeManager.o: mazeManager.cpp extractMaze.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

main.o: main.cpp extractMaze.h player.h playerUtils.h mazeManager.h	#put dependencies here!
>>>>>>> 1cd5d882ddef58a6bbe65e08e7863848c48728da:makefile
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
