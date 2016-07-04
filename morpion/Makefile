CXX=g++
CXXFLAGS=-Wall -W -std=c++17 -O2
CXXLIBS=-fcilkplus
CXXDEF=USE_CILK
LDFLAGS=

all: main.o morpion.o minmax.o
	$(CXX) $^ $(CXXLIBS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $^ -c $(CXXFLAGS) $(CXXLIBS) -D $(CXXDEF)

clean:
	rm *.o
