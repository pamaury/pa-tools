DEFINES=
CC?=gcc
CXX?=g++
LD?=g++
REGTOOLS_DIR=$(PAMAURY_PROJECT_HOME)/rockbox/myrockbox/utils/regtools/
INCLUDE=-I$(REGTOOLS_DIR)/include
CFLAGS=-g -std=c99 -Wall $(DEFINES) $(INCLUDE)
CXXFLAGS=-g -Wall $(DEFINES) $(INCLUDE) -std=gnu++11
LDFLAGS=-L$(REGTOOLS_DIR)/lib -lsocdesc -lxml2
SRC=$(wildcard *.c)
SRCXX=$(wildcard *.cpp)
EXEC=$(SRC:.c=) $(SRCXX:.cpp=)

all: $(EXEC)

%: %.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%: %.cpp $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -fr $(EXEC)

run:
	./jz_preprocess -o jz4760b.parse/ jz4760b/*.h
	./parse2 -o regs-jz4760b.xml jz4760b.parse/*.h
