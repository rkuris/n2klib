#include "n2k.h"
#include "n2ksocket.h"
#include "generated/windData.cc"

#include "pipe.h"

#include <stdio.h>
#include <signal.h>
#include <bits/stdc++.h>

void handleWind(const n2k::Message & m);

std::ostream* out = &std::cout;

int main(int argc, char *argv[])
{
    // if you pass any argument, you skip writing to rrdtool
    if (argc <= 1) {
	    out = new opipestream("rrdtool - >/dev/null");
    }
    signal(SIGINT, exit);
    n2k::SocketCanReceiver r("can0");
    n2k::Callback cb(
        n2k::WindData::PGN,
        n2k::WindData::Type,
        handleWind);
    r.addCallback(cb);
    r.run();
}
void handleWind(const n2k::Message & m)
{
    n2k::WindData w(m);
    *out << "update foo.rrd N:" << std::setprecision(2) <<
        w.getWindSpeed() << ":" << w.getWindAngle() << "\n";
}
