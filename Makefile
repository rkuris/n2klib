.PHONY: tests
CXXFLAGS = -Wall -std=c++11 -pedantic -Wno-psabi

mkmsgs: mkmsgs.cpp pgns.json

tests:
	$(MAKE) -C tests

pgns.json:
	wget https://raw.githubusercontent.com/canboat/canboat/master/analyzer/pgns.json
