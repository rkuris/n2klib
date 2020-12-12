# n2klib

Unsatisifed with the size and quality of the NMEA 2000
libraries out there to interface with CAN, I decided to
do a fresh start. The things I am after:

 - Classes for each message. Since most of the time,
   applications only care about a few NMEA 2000 messages,
   I don't want all the code to encode or decode all of
   them, so they get built into separate files. If your
   code references them, they will be pulled in, otherwise
   not.
 - Separation of packet to message processing. The source
   of packets should be completely abstracted from the
   handling of them. This library primarily deals with
   handling them, with examples of how to get them from
   different environments.
 - Clean API. Create n2k::Receiver, add n2k::Callback,
   and call Receiver:ingest with your packets.
 - Fast discard. If nobody cares about a specific message
   PGN, then don't bother doing anything with it.
 - Autogeneration. Classes should be generated from
   a DSL or another definition file, reducing the chance
   of a coding error on a particular message type.
 - Tests. I am a firm believer that the tests shouldn't
   need access to a CANbus. There should be unit tests
   that prove that each case works correctly.
 - Support for variable length stuff. Most of the libraries
   I saw didn't support things like a set of satellites
   in a message.
 - Minimal (perhaps zero) memory alloctions at runtime.
   Everything should be static if possible. That said,
   I'm sticking with <vector> for callbacks for the
   initial release. It would be nice to give a static
   CallbackList to a receiver.
 - Few dependencies. It needs to compile on arduino, which
   means most of the C++ standard library is off-limits.
   Currently uses <functional> and <vector>, both seems to
   have good implementations on arduino.

# General Usage

First, decide if you want a receiver or a transciever. If
you want to transmit, you must receive for address negotiation.

For a receiver:

    #include "n2k.h"
    #include "generated/temperature.cc"

    n2k::Receiver r;

    void handler(const Packet &p) {
        n2k::Temperature t(p);
	Serial.println(t.getActualTemperature())
    }

    void setup() {
	r.addListener(t, tempHandler)
    }

    void loop() {
	// read a Packet here
	Packet p = ...
	r.ingest(p);
    }

Packet reading itself depends a lot on the device. On a
teensy, you can use an event-based reader; see the examples
directory for details.


