CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: test.o
	$(CXX) $(CXXFLAGS) test.o -o all

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm *.o all