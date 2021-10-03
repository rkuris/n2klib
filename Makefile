.PHONY: tests generated
# no -Wshadow since the inja library has several
CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wwrite-strings -Wno-unused-parameter
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -g
LDFLAGS = -lpthread

mkmsgs: mkmsgs.cpp

all: mkmsgs check distcheck

check: generated

generated: mkmsgs
	./mkmsgs

distcheck: tests

tests:
	$(MAKE) -C tests

.PHONY: docs pgns.json clean check distcheck

pgns.json:
	wget https://raw.githubusercontent.com/canboat/canboat/master/analyzer/pgns.json

docs:
	doxygen

clean:
	rm -fr html latex ./mkmsgs
	+$(MAKE) -C tests $@ $(MAKECMDGOALS)
