CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -O2 
OBJ = my_ls.o
 
all: my_ls 
.PHONY: all	
	
program: $(OBJ1)
	$(CC) $(CFLAGS) -o my_ls $(OBJ1)


%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.o my_ls 
