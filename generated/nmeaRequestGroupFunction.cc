// class NmeaRequestGroupFunction

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: NMEA - Request group function
#include "../n2k.h"
namespace n2k {
  class NmeaRequestGroupFunction : public Message {
  public:
    NmeaRequestGroupFunction(const Message &m) : Message(m) {};
    double getFunctionCode() { return 1.000000 * Get(0,8); };
    double getPgn() { return 1.000000 * Get(8,24); };
    double getTransmissionInterval() { return 0.001000 * Get(32,32); };
    double getTransmissionIntervalOffset() { return 0.010000 * Get(64,16); };
    unsigned char getOfParameters() { return Get(80,8); };
    double getParameter() { return 1.000000 * Get(88,8); };
    unsigned char getValue() { return Get(96,0); };
    static const pgn_t PGN = 126208;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() { return PGN; }
  };
}
