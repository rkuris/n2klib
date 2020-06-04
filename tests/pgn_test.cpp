#include "../pgn.h"
struct tc {
	canid_t canid;
	prio_t  priority;
	pgn_t   pgn;
	addr_t  src;
	addr_t  dst;
} testcases[] = {
	{0x1ce811a0, 7, 0xe800, 0xa0, 0x11},
	{0x1cff52a0, 7, 0xff52, 0xa0, 0xff}
};

int main(int argc, char *argv[]) {
	/* decoder test */
	for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
		tc testcase = testcases[i];
		assert(getPGN(testcase.canid) == testcase.pgn);
		assert(getPriority(testcase.canid) == testcase.priority);
		assert(getSource(testcase.canid) == testcase.src);
		assert(getDestination(testcase.canid) == testcase.dst);
	}
	/* encoder test */
	for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
		tc testcase = testcases[i];
		canid_t canid = 0;
		setPGN(canid, testcase.pgn);
		setPriority(canid, testcase.priority);
		setSource(canid, testcase.src);
		if (testcase.dst != 0xff) {
			setDestination(canid, testcase.dst);
		}
		assert(canid == testcase.canid);
	}

	return 0;
}
