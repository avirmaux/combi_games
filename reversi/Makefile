CXX=g++
CXXFLAGS=-Wall -W -std=c++17 -O2
# CXXLIBS=-fcilkplus
# CXXDEF=-D _VERBOSE
LDFLAGS=

all:  reversi.o misc.o search.o evaluate.o main.o
	$(CXX) $^ $(CXXLIBS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $^ -c $(CXXFLAGS) $(CXXLIBS) $(CXXDEF)

.PHONY:
clean:
	rm *.o
