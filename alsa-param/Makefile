CC=gcc
CFLAGS=-W -Wall -O2 `pkg-config --cflags alsa` -std=c99 -g
LDFLAGS=`pkg-config --libs alsa` 
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


