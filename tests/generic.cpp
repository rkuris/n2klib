#include "../n2k.h"
#include "../generated/temperature.cc"

#include <cstdio>

using namespace n2k;

void handleTemp(const n2k::Message&);

int main(int argc, char *argv[]) {
	// first, set up a generic receiver
	n2k::Receiver r;

	// then set up some callbacks
	r.addCallback(n2k::Callback(Temperature::PGN, Temperature::Type, handleTemp));

	// connect your packet source to r.ingest()
	// here we're just making up a packet
	n2k::Packet p;
	p.canid = 0;
	p.data[3] = 1;
	p.data[4] = 0;
	p.setPGN(Temperature::PGN);

	r.ingest(p);
}

void handleTemp(const n2k::Message &m) {
	n2k::Temperature t(m);
	assert(t.PGN == 130312);
	printf("t.getActualTemperature() = %f\n", t.getActualTemperature());
	assert(t.getActualTemperature() == 0.01);
}
