// class IsoAddressClaim

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: ISO Address Claim
#include "../n2k.h"
namespace n2k {
  class IsoAddressClaim : public Message {
  public:
    IsoAddressClaim(const Message &m) : Message(m) {};
    unsigned long getUniqueNumber() { return Get(0,21); };
    unsigned short getManufacturerCode() { return Get(21,11); };
    unsigned char getDeviceInstanceLower() { return Get(32,3); };
    unsigned char getDeviceInstanceUpper() { return Get(35,5); };
    unsigned char getDeviceFunction() { return Get(40,8); };
    unsigned char getDeviceClass() { return Get(49,7); };
    enum {
        Reserved_for_2000_Use = 0,
        System_tools = 10,
        Safety_systems = 20,
        Internetwork_device = 25,
        Electrical_Distribution = 30,
        Electrical_Generation = 35,
        Steering_and_Control_surfaces = 40,
        Propulsion = 50,
        Navigation = 60,
        Communication = 70,
        Sensor_Communication_Interface = 75,
        Instrumentation_general_systems = 80,
        External_Environment = 85,
        Internal_Environment = 90,
        Deck_cargo_fishing_equipment_systems = 100,
        Display = 120,
        Entertainment = 125
    };
    unsigned char getSystemInstance() { return Get(56,4); };
    unsigned char getIndustryGroup() { return Get(60,3); };
    enum {
        Global = 0,
        Highway = 1,
        Agriculture = 2,
        Construction = 3,
        Marine = 4,
        Industrial = 5
    };
    static const pgn_t PGN = 60928;
    static const PGNType Type = PGNType::Single;
    pgn_t getPGN() { return PGN; }
  };
}
