all : experiment experimentz

CXX := g++
CXXFLAGS := -O3 -std=c++11 -W -Wall

clean :
	rm -f experiment experimentz

experiment : experiment.cc mwc.h
	$(CXX) $(CXXFLAGS) -o $@ $^

experimentz : experimentz.cc mwcz.h
	$(CXX) $(CXXFLAGS) -o $@ $^

