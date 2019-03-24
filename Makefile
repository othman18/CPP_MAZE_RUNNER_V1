#COMP = g++
#output: main.o
#	$(COMP) main.o -o output
#main.o: main.cpp
#	$(COMP) -std=c++14 -Wall -Wextra \
#	-Werror -pedantic-errors -DNDEBU -c main.cpp
#clean:
#	rm *.o output


COMP = g++ # -4.2.1
#put all your object files here
OBJS = main.o #objects should be placed here! 
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)