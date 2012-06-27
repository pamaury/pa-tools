CC=gcc
CXX=g++
LD=gcc
COMMON_FLAGS=`pcap-config --cflags`
CFLAGS=-std=gnu99 -W -Wall -O2 -g $(COMMON_FLAGS)
CXXFLAGS=-W -Wall -O2 -g $(COMMON_FLAGS)
SRC=$(wildcard *.c)
SRCXX=$(wildcard *.cpp)
LDFLAGS=`pcap-config --libs`
OBJ=$(SRCXX:.cpp=.oxx) $(SRC:.c=.o)
EXEC=mtp_analyzer

all: $(EXEC)

mtp_analyzer: mtp_analyzer.o
	$(LD) -o $@ $< $(LDFLAGS)

%.oxx: %.cpp
	$(CXX) -o -c $@ $< $(CXXFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

veryclean: clean
	rm -f $(EXEC)
