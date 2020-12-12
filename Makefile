.PHONY: tests generated
# no -Wshadow since the inja library has several
CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wwrite-strings -Wno-unused-parameter -Wfloat-equal
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -g
LDFLAGS = -lpthread

all: mkmsgs generated tests

generated: mkmsgs
	./mkmsgs

mkmsgs: mkmsgs.cpp

tests:
	$(MAKE) -C tests

.PHONY: docs pgns.json clean

pgns.json:
	wget https://raw.githubusercontent.com/canboat/canboat/master/analyzer/pgns.json

docs:
	doxygen

clean:
	rm -fr html latex ./mkmsgs
	+$(MAKE) -C tests $@ $(MAKECMDGOALS)
