CXX=g++
CXXFLAGS=-Wall -W -std=c++17 -O2
CXXLIBS=-fcilkplus
CXXDEF=
LDFLAGS=

all: fourinrow.o main.o alphabeta.o montecarlo.o
	$(CXX) $^ $(CXXLIBS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $^ -c $(CXXFLAGS) $(CXXLIBS)

clean:
	rm *.o
