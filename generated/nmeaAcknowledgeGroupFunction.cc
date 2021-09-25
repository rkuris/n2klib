// class NmeaAcknowledgeGroupFunction

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: NMEA - Acknowledge group function
#include "../n2k.h"
namespace n2k {
  class NmeaAcknowledgeGroupFunction : public Message {
  public:
    NmeaAcknowledgeGroupFunction(const Message &m) : Message(m) {};
    double getFunctionCode() { return 1.000000 * Get(0,8); };
    double getPgn() { return 1.000000 * Get(8,24); };
    unsigned char getPgnErrorCode() { return Get(32,4); };
    enum {
        Acknowledge = 0,
        PGN_not_supported = 1,
        PGN_not_available = 2,
        Access_denied = 3,
        Not_supported = 4,
        Tag_not_supported = 5,
        Read_or_Write_not_supported = 6
    };
    unsigned char getTransmissionIntervalPriorityErrorCode() { return Get(36,4); };
    enum {
        Acknowledge = 0,
        Transmit_Interval_Priority_not_supported = 1,
        Transmit_Interval_to_low = 2,
        Access_denied = 3,
        Not_supported = 4
    };
    unsigned char getOfParameters() { return Get(40,8); };
    unsigned char getParameter() { return Get(48,4); };
    enum {
        Acknowledge = 0,
        Invalid_parameter_field = 1,
        Temporary_error = 2,
        Parameter_out_of_range = 3,
        Access_denied = 4,
        Not_supported = 5,
        Read_or_Write_not_supported = 6
    };
    static const pgn_t PGN = 126208;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() { return PGN; }
  };
}
