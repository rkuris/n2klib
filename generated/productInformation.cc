// class ProductInformation

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: Product Information
#include "../n2k.h"
namespace n2k {
  class ProductInformation : public Message {
  public:
    ProductInformation() {};
    ProductInformation(const Message &m) : Message(m) {};
    void setNmea2000Version(unsigned short value) { Set(value,0,16); }
    unsigned short getNmea2000Version() const { return Get(0,16); };
    void setProductCode(unsigned short value) { Set(value,16,16); }
    unsigned short getProductCode() const { return Get(16,16); };
    void setModelId( value) { Set(value,32,256); }
     getModelId() const { return Get(32,256); };
    void setSoftwareVersionCode( value) { Set(value,288,256); }
     getSoftwareVersionCode() const { return Get(288,256); };
    void setModelVersion( value) { Set(value,544,256); }
     getModelVersion() const { return Get(544,256); };
    void setModelSerialCode( value) { Set(value,800,256); }
     getModelSerialCode() const { return Get(800,256); };
    void setCertificationLevel(unsigned char value) { Set(value,1056,8); }
    unsigned char getCertificationLevel() const { return Get(1056,8); };
    void setLoadEquivalency(unsigned char value) { Set(value,1064,8); }
    unsigned char getLoadEquivalency() const { return Get(1064,8); };
    static const pgn_t PGN = 126996;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() const { return PGN; }
  };
}
