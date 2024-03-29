// class PgnListTransmitAndReceive

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: PGN List (Transmit and Receive)
#include "../n2k.h"
namespace n2k {
  class PgnListTransmitAndReceive : public Message {
  public:
    enum class FunctionCode:unsigned char {
      Transmit_PGN_list = 0,
      Receive_PGN_list = 1
    };

    PgnListTransmitAndReceive() {};
    PgnListTransmitAndReceive(const Message &m) : Message(m) {};
    void setFunctionCode(FunctionCode value) { Set((unsigned char)value,0,8); }
    FunctionCode getFunctionCode() const { return (FunctionCode)Get(0,8); };
    void setPgn(unsigned long value) { Set(value,8,24); }
    unsigned long getPgn() const { return Get(8,24); };
    static const pgn_t PGN = 126464;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() const { return PGN; }
  };
}
