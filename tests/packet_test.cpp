#include "../n2k.h"
struct tc {
	n2k::canid_t canid;
	n2k::prio_t  priority;
	n2k::pgn_t   pgn;
	n2k::addr_t  src;
	n2k::addr_t  dst;
} testcases[] = {
	{0x1ce811a0, 7, 0xe800, 0xa0, 0x11},
	{0x1cff52a0, 7, 0xff52, 0xa0, 0xff}
};

int main(int argc, char *argv[]) {
	/* decoder test */
	for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
		tc testcase = testcases[i];
		n2k::Packet p;
		p.canid = testcase.canid;
		assert(p.getPGN() == testcase.pgn);
		assert(p.getPriority() == testcase.priority);
		assert(p.getSource() == testcase.src);
		assert(p.getDestination() == testcase.dst);
	}
	/* encoder test */
	for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
		tc testcase = testcases[i];
		n2k::Packet p;
		p.setPGN(testcase.pgn);
		p.setPriority(testcase.priority);
		p.setSource(testcase.src);
		if (testcase.dst != 0xff) {
			p.setDestination(testcase.dst);
		}
		assert(p.canid == testcase.canid);
	}

	return 0;
}
