CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -g

.PHONY: test clean

test: packet_test generic
	./packet_test
	./generic

packet_test: packet_test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

generic: generic.cpp ../n2k.h
	$(CXX) $(CXXFLAGS) $< -o $@


clean:
	rm ./packet_test ./generic
