/*!
 * \file n2ksocket.h
 * \brief Socket CAN (Linux only)
 *
 * Use this header on linux (and raspberry pi) to get
 * something that can read the canbus directly.
 */
#pragma once

#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <system_error>

namespace n2k {
/*! \brief Receiver for Linux CANbus devices
 *
 * SocketCanReceiver is a Receiver that understands
 * linux canbus devices. Normally you'd initialize the
 * socket like this:
 *
 *      ip link set dev can0 type can bitrate 250000
 *      ip link set can0 up
 *
 * Then, construct the SocketCanReceiver by passing it
 * "can0" as the device name.
 *
 * Once you've added callbacks, just call run(), which
 * reads packets and ingests them. It doesn't return.
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
    /*! \brief Move some filtering to the kernel
     *
     * Call this method after you've set up all your callbacks.
     * It works best if there are only a few callbacks; if you
     * have a lot of callbacks, or want to process most of the
     * messages, you probably should skip this.
     */
    void applyKernelFilter() {
      auto callbackSize = mCallbackList->mCallbacks.size();
      struct can_filter *filters = (struct can_filter *)calloc(callbackSize, sizeof(struct can_filter));
      int n = 0;
      for (auto it = std::begin (mCallbackList->mCallbacks);
	   it != std::end (mCallbackList->mCallbacks); ++it)
	{
	    filters[n].can_id = it->mpgn << 8;
	    if ((it->mpgn & 0xf00000) == 0xf00000) {
	        filters[n].can_mask = 0x1ffff00;
	    } else {
	        filters[n].can_mask = 0x1ff0000;
	    }
	    n++;
	}
      setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, filters, sizeof(struct can_filter)*callbackSize);
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
