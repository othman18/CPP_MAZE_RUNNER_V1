COMP = g++#-5.3.0
#put all your object files here
OBJS = main.o extractMaze.o 	#objects should be placed here! 


CPP_LINK_FLAG = -lstdc++fs


#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG #-lstdc++fs


$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@ #$(CPP_LINK_FLAG)
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies

extractMaze.o: extractMaze.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 

main.o: main.cpp extractMaze.h	#put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)