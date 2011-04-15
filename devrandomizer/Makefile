CC=gcc
CXX=g++
CFLAGS=-W -Wall -O2 -std=c99 -g
CXXFLAGS=-W -Wall -O2
LDFLAGS=
SRC=$(wildcard *.c)
SRCXX=$(wildcard *.cpp)
OBJ=$(SRC:.c=) $(SRCXX:.cpp=)

all: $(OBJ)

%: %.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)
	
%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(OBJ)


