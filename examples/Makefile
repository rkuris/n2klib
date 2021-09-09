CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -g

tests: candump_reader
	./candump_reader < testdata/candump-output.txt 2>/tmp/candump.errs | diff - testdata/stdout
	diff /tmp/candump.errs testdata/stderr

candump_reader: candump_reader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: indent tests
indent:
	indent -kr *.cpp *.h
