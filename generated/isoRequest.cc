// class IsoRequest

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: ISO Request
#include "../n2k.h"
namespace n2k {
  class IsoRequest : public Message {
  public:
    IsoRequest() {};
    IsoRequest(const Message &m) : Message(m) {};
    void setPgn(unsigned long value) { Set(value,0,24); }
    unsigned long getPgn() const { return Get(0,24); };
    static const pgn_t PGN = 59904;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() const { return PGN; }
  };
}
