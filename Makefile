CXX = g++
CXXFLAGS = -Wall -I/usr/include/eigen3/ -lnabo -fopenmp -std=c++11

main: entropy.cpp
	$(CXX) entropy.cpp -o main $(CXXFLAGS)
