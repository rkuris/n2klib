// class WindData

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: Wind Data
#include "../n2k.h"
namespace n2k {
  class WindData : public Message {
  public:
    WindData(const Message &m) : Message(m) {};
    unsigned char getSid() { return Get(0,8); };
    double getWindSpeed() { return 0.019438 * Get(8,16); };
    double getWindAngle() { return 0.005730 * Get(24,16); };
    unsigned char getReference() { return Get(40,3); };
    enum {
        True_ground_referenced_to_North_ = 0,
        Magnetic_ground_referenced_to_Magnetic_North_ = 1,
        Apparent = 2,
        True_boat_referenced_ = 3,
        True_water_referenced_ = 4
    };
    static const pgn_t PGN = 130306;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() { return PGN; }
  };
}
