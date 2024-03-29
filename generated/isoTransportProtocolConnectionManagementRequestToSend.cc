// class IsoTransportProtocolConnectionManagementRequestToSend

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: ISO Transport Protocol, Connection Management - Request To Send
#include "../n2k.h"
namespace n2k {
  class IsoTransportProtocolConnectionManagementRequestToSend : public Message {
  public:
    IsoTransportProtocolConnectionManagementRequestToSend() {};
    IsoTransportProtocolConnectionManagementRequestToSend(const Message &m) : Message(m) {};
    void setGroupFunctionCode(unsigned char value) { Set(value,0,8); }
    unsigned char getGroupFunctionCode() const { return Get(0,8); };
    void setMessageSize(unsigned short value) { Set(value,8,16); }
    unsigned short getMessageSize() const { return Get(8,16); };
    void setPackets(unsigned char value) { Set(value,24,8); }
    unsigned char getPackets() const { return Get(24,8); };
    void setPacketsReply(unsigned char value) { Set(value,32,8); }
    unsigned char getPacketsReply() const { return Get(32,8); };
    void setPgn(unsigned long value) { Set(value,40,24); }
    unsigned long getPgn() const { return Get(40,24); };
    static const pgn_t PGN = 60416;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() const { return PGN; }
  };
}
