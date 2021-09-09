#include "../n2k.h"
#include "../generated/windData.cc"

#include <cstdio>
#include <istream>
#include <fstream>
#include <iostream>

using namespace n2k;

#include "candump_reader.h"

namespace flags {
    bool debugging = false;
} n2k::Packet & fromCandumpText(std::istream & s)
{
    char line[80];
    s.getline(line, sizeof(line));

    unsigned int canid;
    int datalen;
    int consumed;
    auto seen =
	sscanf(line, " %*s %8X [%1d] %n", &canid, &datalen, &consumed);
    if (seen < 2) {
	throw std::invalid_argument("input line '" +
				    std::string(line) +
				    "' didn't look like 'devname XXXXXXXX [N] ...");
    }
    if (datalen > 8) {
	throw std::invalid_argument("input line '" +
				    std::string(line) +
				    "' had more than 8 data bytes");
    }

    static Packet p;
    p.canid = canid;
    int offset = 0;
    while (datalen--) {
	unsigned int data;
	seen = sscanf(line + consumed, "%x", &data);
	consumed += 3;
	p.data[offset++] = data;
    }
    if (flags::debugging) {
	std::cerr << line << "\n";
    }
    return p;
}

void handleWind(const n2k::Message & m);

int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], "--debug")) {
	flags::debugging = true;
    }

    n2k::Receiver r;
    r.addCallback(n2k::Callback
		  (WindData::PGN, WindData::Type, handleWind));

    std::cin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    int errs = 0;
    for (;;) {
	try {
	    auto p = fromCandumpText(std::cin);
	    r.ingest(p);
	}
	catch(std::ifstream::failure &) {
	    if (std::cin.eof()) {
		exit(0);
	    }
	    throw;
	}
	catch(std::invalid_argument & i) {
	    std::cerr << i.what() << "\n";
	    if (errs++ > 10) {
		std::cerr << "Too many errors; quitting\n";
		exit(1);
	    }
	}
    }
}

void handleWind(const n2k::Message & m)
{
    n2k::WindData w(m);
    printf("update foo.rrd N:%f:%f\n", w.getWindSpeed(), w.getWindAngle());
}
