#include "n2k.h"
#include "n2ksocket.h"
#include "generated/windData.cc"

// This is my least favorite example, because it relies on
// a library that has a terrible interface; an example is
// that you can only specify the wind speed in m/s, and I
// have knots.
//
// In any case, I was able to get it to produce output to
// stdout on my pi. To feed this to opencpn, for example,
// you need to have /dev/tnt working from here:
//   https://github.com/freemed/tty0tty.git
// Then, have opencpn read from /dev/tnt0 and have this
// program output to /dev/tnt1 using standard redirection:
//   n2kto0183 > /dev/tnt1
// End result: apparent wind speed and direction are available
// in opencpn!

#include "NMEA0183.h"
#include "NMEA0183Messages.h"
#include "NMEA0183LinuxStream.h"

void handleWind(const n2k::Message & m);
tNMEA0183LinuxStream outStream("/dev/stdout");
tNMEA0183 out(&outStream);

int main(int argc, char *argv[])
{
    n2k::SocketCanReceiver r("can0");
    n2k::Callback cb(
        n2k::WindData::PGN,
        n2k::WindData::Type,
        handleWind);
    r.addCallback(cb);
    r.applyKernelFilter();
    r.run();
}
void handleWind(const n2k::Message & m)
{
    n2k::WindData w(m);
    const double kKnots2MPS = 1.944;
    tNMEA0183Msg msg;
    tNMEA0183WindReference WindReference;
    if (w.getReference() == n2k::WindData::Apparent) {
        WindReference = NMEA0183Wind_Apparent;
    } else {
	WindReference = NMEA0183Wind_True;
    }
    if (NMEA0183SetMWV(msg, w.getWindAngle(), WindReference, w.getWindSpeed()/kKnots2MPS)) {
        out.SendMessage(msg);
    }
}
extern "C" uint32_t millis();
uint32_t millis() { return 0; }
