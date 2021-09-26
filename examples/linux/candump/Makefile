CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wno-unused-function
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -O -I../../..

tests: candump_reader
	./candump_reader -i testdata/candump-output.txt 2>/tmp/candump.errs | diff - testdata/stdout
	diff /tmp/candump.errs testdata/stderr

candump_reader: candump_reader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: astyle tests
astyle:
	astyle -n *.cpp *.h
