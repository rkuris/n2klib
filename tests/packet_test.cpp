#include "../n2k.h"

void packetDecoder() {
    struct tc {
        n2k::canid_t canid;
        n2k::prio_t  priority;
        n2k::pgn_t   pgn;
        n2k::addr_t  src;
        n2k::addr_t  dst;
    } testcases[] = {
        {0x1ce811a0, 7, 0xe800, 0xa0, 0x11},
        {0x1dff80a0, 7, 130944, 0xa0, 0xff}
    };
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
        assert((p.canid & (~n2k::EFF_FRAME)) == testcase.canid);
    }
}

void pgnEncodeDecode() {
    auto validPGNs =
    {   59392, 59904, 60160, 60416, 60928, 61184, 61440, 65001,
        65002, 65003, 65004, 65005, 65006, 65007, 65008, 65009,
        65010, 65011, 65012, 65013, 65014, 65015, 65016, 65017,
        65018, 65019, 65020, 65021, 65022, 65023, 65024, 65025,
        65026, 65027, 65028, 65029, 65030, 65240, 65280, 65284,
        65285, 65286, 65287, 65288, 65289, 65290, 65292, 65293,
        65309, 65312, 65325, 65341, 65345, 65359, 65360, 65361,
        65371, 65374, 65379, 65408, 65409, 65410, 65480, 65536,
        126208, 126464, 126720, 126976, 126983, 126984, 126985, 126986,
        126987, 126988, 126992, 126993, 126996, 126998, 127233, 127237,
        127245, 127250, 127251, 127252, 127257, 127258, 127488, 127489,
        127493, 127496, 127497, 127498, 127500, 127501, 127502, 127503,
        127504, 127505, 127506, 127507, 127508, 127509, 127510, 127511,
        127512, 127513, 127514, 127744, 127745, 127746, 127750, 127751,
        128000, 128006, 128007, 128008, 128259, 128267, 128275, 128520,
        128776, 128777, 128778, 129025, 129026, 129027, 129028, 129029,
        129033, 129038, 129039, 129040, 129041, 129044, 129045, 129283,
        129284, 129285, 129291, 129301, 129302, 129538, 129539, 129540,
        129541, 129542, 129545, 129546, 129547, 129549, 129550, 129551,
        129556, 129792, 129793, 129794, 129795, 129796, 129797, 129798,
        129799, 129800, 129801, 129802, 129803, 129804, 129805, 129806,
        129807, 129808, 129809, 129810, 130060, 130061, 130064, 130065,
        130066, 130067, 130068, 130069, 130070, 130071, 130072, 130073,
        130074, 130306, 130310, 130311, 130312, 130313, 130314, 130315,
        130316, 130320, 130321, 130322, 130323, 130324, 130560, 130567,
        130569, 130570, 130571, 130572, 130573, 130574, 130576, 130577,
        130578, 130579, 130580, 130581, 130582, 130583, 130584, 130585,
        130586, 130816, 130817, 130818, 130819, 130820, 130821, 130823,
        130824, 130827, 130828, 130831, 130832, 130834, 130835, 130836,
        130837, 130838, 130839, 130840, 130842, 130843, 130845, 130846,
        130847, 130850, 130851, 130856, 130880, 130881, 130944
    };
    n2k::Packet p;
    for (auto it = validPGNs.begin(); it != validPGNs.end(); ++it) {
        p.canid = 0;
        p.setPGN(*it);
        assert(p.getPGN() == *it);
    }
}

void bitUnpacker() {
    struct tc {
        unsigned char data[n2k::Message::MAX_NMEA_DATA];
        int start;
        int len;
        unsigned long expected;
    } testcases[] = {
        {"\01", 0, 1, 1},
        {"", 0, 1, 0},
        {"", 0, 2, 0},
        {"", 0, 7, 0},
        {"\0\01", 8, 1, 1},
        {"\0\01", 8, 2, 2},
        {"\0\02", 8, 2, 1},
        {"\x80\01", 0, 9, 0x101}
    };

    for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
        tc testcase = testcases[i];
        n2k::Message m;
        memcpy(m.data, testcase.data, sizeof(testcase.data));
        auto got = m.Get(testcase.start, testcase.len);
        ASSERT(got == testcase.expected,
               "case " << i <<
               ": expected " << testcase.expected <<
               " got " << got);
    }
}

int main(int argc, char *argv[]) {
    pgnEncodeDecode();
    packetDecoder();
    bitUnpacker();
    return 0;
}
