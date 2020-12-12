// class IsoTransportProtocolConnectionManagementRequestToSend

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: ISO Transport Protocol, Connection Management - Request To Send
#include "../n2k.h"
namespace n2k {
  class IsoTransportProtocolConnectionManagementRequestToSend : public Message {
  public:
    IsoTransportProtocolConnectionManagementRequestToSend(const Message &m) : Message(m) {};
    unsigned char getGroupFunctionCode() { return Get(0,8); };
    unsigned short getMessageSize() { return Get(8,16); };
    unsigned char getPackets() { return Get(24,8); };
    unsigned char getPacketsReply() { return Get(32,8); };
    double getPgn() { return 1.000000 * Get(40,24); };
    static const pgn_t PGN = 60416;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() { return PGN; }
  };
}
