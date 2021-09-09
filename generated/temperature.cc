// class Temperature

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: Temperature
#include "../n2k.h"
namespace n2k {
  class Temperature : public Message {
  public:
    Temperature(const Message &m) : Message(m) {};
    unsigned char getSid() { return Get(0,8); };
    unsigned char getInstance() { return Get(8,8); };
    unsigned char getSource() { return Get(16,8); };
    enum {
        Sea_Temperature = 0,
        Outside_Temperature = 1,
        Inside_Temperature = 2,
        Engine_Room_Temperature = 3,
        Main_Cabin_Temperature = 4,
        Live_Well_Temperature = 5,
        Bait_Well_Temperature = 6,
        Refrigeration_Temperature = 7,
        Heating_System_Temperature = 8,
        Dew_Point_Temperature = 9,
        Apparent_Wind_Chill_Temperature = 10,
        Theoretical_Wind_Chill_Temperature = 11,
        Heat_Index_Temperature = 12,
        Freezer_Temperature = 13,
        Exhaust_Gas_Temperature = 14
    };
    double getActualTemperature() { return 0.010000 * Get(24,16); };
    double getSetTemperature() { return 0.010000 * Get(40,16); };
    static const pgn_t PGN = 130312;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() { return PGN; }
  };
}
