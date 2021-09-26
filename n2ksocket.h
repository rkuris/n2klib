#pragma once

#include <linux/can.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <system_error>

namespace n2k {
/*! SocketCanReceiver is a Receiver that understands
 *  linux canbus devices. Normally you'd initialize the
 *  socket like this:
 *
 *      ip link set dev can0 type can bitrate 250000
 *      ip link set can0 up
 *
 *  Then, construct the SocketCanReceiver by passing it
 *  "can0" as the device name.
 *
 *  Once you've added callbacks, just call run(), which
 *  reads packets and ingests them. It doesn't return.
*/
class SocketCanReceiver : public Receiver
{
public:
    /*! Construct a SocketCanReceiver. The string passed
     *  in is the name of the device, such as "can0".
     */
    SocketCanReceiver(const char *ifname_) : ifname(ifname_) {
        struct sockaddr_can addr;
        struct ifreq ifr;

        if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0 ) {
            throw std::system_error(errno, std::generic_category());
        }

        strncpy(ifr.ifr_name, ifname_, sizeof(ifr.ifr_name));
        ioctl(sock, SIOCGIFINDEX, &ifr);

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            throw std::system_error(errno, std::generic_category(), ifname);
        }
    }
    /*! run reads canbus frames, turns them into packets,
     *  and ingests them. It doesn't return. You can run
     *  this in a different thread if you need to do
     *  something else at the same time.
     *
     *  It can throw a std::system_error if the read fails.
     */
    void run() {
        struct can_frame frame;
        for (;;) {
            int nbytes = read(sock, &frame, sizeof(struct can_frame));

            if (nbytes < 0) {
                throw std::system_error(errno, std::generic_category(), ifname);
            }

            if (nbytes < (int)sizeof(struct can_frame)) {
                // skip incomplete frames
                continue;
            }
            Packet p(frame.can_id, frame.data);
            ingest(p);
        }
    }

protected:
    int sock;
private:
    std::string ifname;
};
}
