CXX = g++
CXXFLAGS = -Wall -I /usr/include/flann/

main: entropy.cpp
	$(CXX) entropy.cpp -o entropy $(CXXFLAGS)
