#include "n2k.h"
#include "n2ksocket.h"
#include "generated/windData.cc"

void handleWind(const n2k::Message & m);

int main(int argc, char *argv[])
{
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
    printf("speed: %.1f angle: %.1f\n",
           w.getWindSpeed(), w.getWindAngle());
}
