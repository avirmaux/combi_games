CXX=g++
CXXFLAGS=-Wall -W -std=c++17 -g
# CXXLIBS=-fcilkplus
# CXXDEF=-D _VERBOSE
LDFLAGS=

OBJS = reversi.o misc.o search.o evaluate.o main.o

all: $(OBJS)
	$(CXX) $^ $(CXXLIBS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $^ -c $(CXXFLAGS) $(CXXLIBS) $(CXXDEF)

.PHONY:
clean:
	@rm $(OBJS)
