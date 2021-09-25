// class ProductInformation

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: Product Information
#include "../n2k.h"
namespace n2k {
  class ProductInformation : public Message {
  public:
    ProductInformation(const Message &m) : Message(m) {};
    unsigned short getNmea2000Version() { return Get(0,16); };
    unsigned short getProductCode() { return Get(16,16); };
     getModelId() { return Get(32,256); };
     getSoftwareVersionCode() { return Get(288,256); };
     getModelVersion() { return Get(544,256); };
     getModelSerialCode() { return Get(800,256); };
    unsigned char getCertificationLevel() { return Get(1056,8); };
    unsigned char getLoadEquivalency() { return Get(1064,8); };
    static const pgn_t PGN = 126996;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() { return PGN; }
  };
}
