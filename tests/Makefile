CXXFLAGS = -Wall -std=c++11 -pedantic -Wno-psabi

.PHONY: test

test: pgn_test
	./pgn_test

pgn_test: pgn_test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
