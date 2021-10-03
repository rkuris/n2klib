#include "n2k.h"
#include "n2ksocket.h"
#include "generated/windData.cc"
#include "generated/speed.cc"

// This is my least favorite example, because it relies on
// a library that has a terrible interface; an example is
// that you can only specify the wind speed in m/s, and I
// have knots. So, the handler methods are huge -- you have
// to babysit the NMEA0183 library. Is that the next thing
// I should rewrite?
//
// In any case, I was able to get it to produce output to
// stdout on my pi. To feed this to opencpn, for example,
// you need to have /dev/tnt working from here:
//   https://github.com/freemed/tty0tty.git
// Then, have opencpn read from /dev/tnt0 and have this
// program output to /dev/tnt1 using standard redirection:
//   n2kto0183 > /dev/tnt1
// End result: apparent wind speed and direction are available
// as well as STW in opencpn!
//
// I also had a problem where the wind speed info is sent
// over n2k 10 times, with exactly the same data, so I added
// code to reduce the amount of noise on the 0183 bus and save
// some CPU time.

#include "NMEA0183.h"
#include "NMEA0183Messages.h"
#include "NMEA0183LinuxStream.h"

void handleWind(const n2k::Message & m);
void handleSpeed(const n2k::Message & m);
tNMEA0183LinuxStream outStream("/dev/stdout");
tNMEA0183 out(&outStream);

using Reference = n2k::WindData::Reference;

int main(int argc, char *argv[])
{
    n2k::SocketCanReceiver r("can0");
    r.addCallback({n2k::WindData::PGN, n2k::WindData::Type, handleWind});
    r.addCallback({n2k::Speed::PGN, n2k::Speed::Type, handleSpeed});
    r.applyKernelFilter();
    r.run();
}
void handleWind(const n2k::Message & m)
{
    static n2k::WindData last;
    static int repeatCount;
    const int kRepeatLimit = 10;
    n2k::WindData w(m);

    if ((repeatCount++ < kRepeatLimit)
     && (last.getWindAngle() == w.getWindAngle())
     && (last.getWindSpeed() == w.getWindSpeed())) {
	    return;
    }
    last = w;
    repeatCount = 0;
    const double kKnots2MPS = 1.944;
    tNMEA0183Msg msg;
    tNMEA0183WindReference WindReference;
    if (w.getReference() == Reference::Apparent) {
        WindReference = NMEA0183Wind_Apparent;
    } else {
        WindReference = NMEA0183Wind_True;
    }
    if (NMEA0183SetMWV(msg, w.getWindAngle(), WindReference, w.getWindSpeed()/kKnots2MPS)) {
        out.SendMessage(msg);
    }
}
void handleSpeed(const n2k::Message & m)
{
    n2k::Speed s(m);
    tNMEA0183Msg msg;
    if (NMEA0183SetVHW(msg, NMEA0183DoubleNA, NMEA0183DoubleNA, s.getSpeedWaterReferenced())) {
        out.SendMessage(msg);
    }
}
extern "C" uint32_t millis();
uint32_t millis() {
    return 0;
}
