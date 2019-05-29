COMP = g++-8.3.0

SHARED_OBJS = _player_a.so _player_b.so
OBJS = _player_a.o _player_b.o

CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
CPP_LINK_FLAG = -shared

all: $(SHARED_OBJS)

_player_a.so: _player_a.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

_player_b.so: _player_b.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

_player_a.o: _player_a.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

_player_b.o: _player_b.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(SHARED_OBJS)
