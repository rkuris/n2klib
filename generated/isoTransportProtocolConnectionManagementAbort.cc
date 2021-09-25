// class IsoTransportProtocolConnectionManagementAbort

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: ISO Transport Protocol, Connection Management - Abort
#include "../n2k.h"
namespace n2k {
  class IsoTransportProtocolConnectionManagementAbort : public Message {
  public:
    IsoTransportProtocolConnectionManagementAbort() {};
    IsoTransportProtocolConnectionManagementAbort(const Message &m) : Message(m) {};
    unsigned char getGroupFunctionCode() { return Get(0,8); };
    unsigned char getReason() { return Get(8,8); };
    double getPgn() { return 1.000000 * Get(32,24); };
    static const pgn_t PGN = 60416;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() { return PGN; }
  };
}
