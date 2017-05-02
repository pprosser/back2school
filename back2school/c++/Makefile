all : experiment experimentz

CXX := g++
CXXFLAGS := -O3 -std=c++11 -W -Wall

experiment : experiment.cc mwc.h
	$(CXX) $(CXXFLAGS) -o $@ $^

experimentz : experimentz.cc mwc.h
	$(CXX) $(CXXFLAGS) -o $@ $^

