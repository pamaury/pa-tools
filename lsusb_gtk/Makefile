CC=gcc
CXX=g++
CFLAGS=-W -Wall -O2 `pkg-config --cflags libusb-1.0` -std=c99 -g
CXXFLAGS=-W -Wall -O2 `pkg-config --cflags gtkmm-2.4` -g
LDFLAGS=`pkg-config --libs libusb-1.0` `pkg-config --libs gtkmm-2.4`
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


