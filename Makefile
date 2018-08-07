CXX = g++
CXXFLAGS = -Wall -I/usr/include/flann/ -lhdf5 -llz4

main: entropy.cpp
	$(CXX) entropy.cpp -o entropy $(CXXFLAGS)
