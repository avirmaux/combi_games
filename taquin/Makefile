CXX=g++
CXXFLAGS=-Wall -W -std=c++17
# CXXLIBS=-fcilkplus
# CXXDEF=-D _VERBOSE
LDFLAGS=

all:  main.o
	$(CXX) $^ $(CXXLIBS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $^ -c $(CXXFLAGS) $(CXXLIBS) $(CXXDEF)

clean:
	rm *.o
