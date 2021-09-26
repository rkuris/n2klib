CXXWARNS = -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wno-unused-function
CXXFLAGS = $(CXXWARNS) -std=c++11 -pedantic -Wno-psabi -g -pg -I../../..
NMEA0183SRC = $(HOME)/NMEA0183

all: wind2rrd simple
reallyall: all n2kto0183

wind2rrd: wind2rrd.cpp pipe.h
	$(CXX) $(CXXFLAGS) $< -o $@

simple: simple.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

n2kto0183: n2kto0183.cpp n2kto0183.lib
	$(CXX) $(CXXFLAGS) -I$(NMEA0183SRC) $^ -o $@

n2kto0183.lib:	$(NMEA0183SRC)/NMEA0183.cpp \
		$(NMEA0183SRC)/NMEA0183Messages.cpp \
		$(NMEA0183SRC)/NMEA0183Msg.cpp \
		$(NMEA0183SRC)/NMEA0183Stream.cpp \
		$(NMEA0183SRC)/NMEA0183LinuxStream.cpp
	$(CXX) -I$(NMEA0183SRC) -c $^
	$(AR) -rcv $@ $(patsubst %.cpp,%.o,$^)

.PHONY: astyle all clean
astyle:
	astyle -n *.cpp *.h

clean:
	rm wind2rrd simple
