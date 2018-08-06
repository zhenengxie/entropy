CXX = g++
CXXFLAGS = -Wall -g -I /usr/include/eigen3

main: entropy.cpp
	$(CXX) $(CXXFLAGS) entropy.cpp
