// class PgnListTransmitAndReceive

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: PGN List (Transmit and Receive)
#include "../n2k.h"
namespace n2k {
  class PgnListTransmitAndReceive : public Message {
  public:
    PgnListTransmitAndReceive(const Message &m) : Message(m) {};
    unsigned char getFunctionCode() { return Get(0,8); };
    enum {
        Transmit_PGN_list = 0,
        Receive_PGN_list = 1
    };
    double getPgn() { return 1.000000 * Get(8,24); };
    static const pgn_t PGN = 126464;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() { return PGN; }
  };
}
