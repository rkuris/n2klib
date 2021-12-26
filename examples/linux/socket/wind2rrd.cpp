#include "n2k.h"
#include "n2ksocket.h"
#include "generated/windData.cc"
#include "generated/waterDepth.cc"
#include "generated/vesselHeading.cc"

#include "pipe.h"

#include <stdio.h>
#include <signal.h>
#include <bits/stdc++.h>

void handleWind(const n2k::Message & m);
void handleDepth(const n2k::Message & m);
void handleHeading(const n2k::Message & m);

std::ostream* out = &std::cout;

int main(int argc, char *argv[])
{
    // if you pass any argument, you skip writing to rrdtool
    if (argc <= 1) {
	    out = new opipestream("rrdtool - >/dev/null");
    }
    signal(SIGINT, exit);
    n2k::SocketCanReceiver r("can0");
    int callbackCount = 0;
    if (access("wind.rrd", W_OK) || argc > 1) {
    n2k::Callback cb(
        n2k::WindData::PGN,
        n2k::WindData::Type,
        handleWind);
    r.addCallback(cb);
    callbackCount++;
    }
    if (access("depth.rrd", W_OK) || argc > 1) {
    n2k::Callback cb2(
        n2k::WaterDepth::PGN,
        n2k::WaterDepth::Type,
        handleDepth);
    r.addCallback(cb2);
    callbackCount++;
    }
    if (access("heading.rrd", W_OK) || argc > 1) {
    n2k::Callback cb3(
        n2k::VesselHeading::PGN,
        n2k::VesselHeading::Type,
        handleHeading);
    r.addCallback(cb3);
    callbackCount++;
    }

    if (callbackCount == 0) {
	std::cerr << "No writeable rrd files!\n";
	exit(1);
    }

    r.applyKernelFilter();
    r.run();
}
void handleWind(const n2k::Message & m)
{
    static n2k::WindData last;
    static int repeatCount;
    const int kRepeatLimit = 10;
    const n2k::WindData &w = static_cast<const n2k::WindData&>(m);

    if ((repeatCount++ < kRepeatLimit)
     && (w.getWindSpeedKnots() == last.getWindSpeedKnots())
     && (w.getWindAngleDegrees() == last.getWindAngleDegrees())) {
	    return;
    }
    last = w;
    repeatCount = 0;
    *out << "update wind.rrd N:" << std::setprecision(2) <<
        w.getWindSpeedKnots() << ":" << w.getWindAngleDegrees() << "\n";
}
void handleDepth(const n2k::Message & m)
{
    const n2k::WaterDepth &d = static_cast<const n2k::WindData&>(m);
    *out << "update depth.rrd N:" << std::setprecision(2) <<
	    d.getDepthFeet() << "\n";
}
void handleHeading(const n2k::Message & m)
{
    static double last;
    static int repeatCount;
    const int kRepeatLimit = 10;
    const n2k::VesselHeading &h = static_cast<const n2k::WindData&>(m);

    auto diff = last - h.getHeadingDegrees();
    if ((repeatCount++ < kRepeatLimit)
     && (diff < .1 && diff > -.1)) {
	    return;
    }
    last = h.getHeadingDegrees();
    repeatCount = 0;

    *out << "update heading.rrd N:" << std::setprecision(2) <<
	    h.getHeadingDegrees() << "\n";
}
