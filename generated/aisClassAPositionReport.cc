// class AisClassAPositionReport

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: AIS Class A Position Report
#include "../n2k.h"
namespace n2k {
  class AisClassAPositionReport : public Message {
  public:
    enum class RepeatIndicator:unsigned char {
      Initial = 0,
      First_retransmission = 1,
      Second_retransmission = 2,
      Final_retransmission = 3
    };

    enum class PositionAccuracy:unsigned char {
      Low = 0,
      High = 1
    };

    enum class Raim:unsigned char {
      not_in_use = 0,
      in_use = 1
    };

    enum class TimeStamp:unsigned char {
      Not_available = 60,
      Manual_input_mode = 61,
      Dead_reckoning_mode = 62,
      Positioning_system_is_inoperative = 63
    };

    enum class AisTransceiverInformation:unsigned char {
      Channel_A_VDL_reception = 0,
      Channel_B_VDL_reception = 1,
      Channel_A_VDL_transmission = 2,
      Channel_B_VDL_transmission = 3,
      Own_information_not_broadcast = 4,
      Reserved = 5
    };

    enum class NavStatus:unsigned char {
      Under_way_using_engine = 0,
      At_anchor = 1,
      Not_under_command = 2,
      Restricted_maneuverability = 3,
      Constrained_by_her_draught = 4,
      Moored = 5,
      Aground = 6,
      Engaged_in_Fishing = 7,
      Under_way_sailing = 8,
      Hazardous_material_High_Speed = 9,
      Hazardous_material_Wing_in_Ground = 10,
      AIS_SART = 14
    };

    enum class SpecialManeuverIndicator:unsigned char {
      Not_available = 0,
      Not_engaged_in_special_maneuver = 1,
      Engaged_in_special_maneuver = 2,
      Reserved = 3
    };

    AisClassAPositionReport() {};
    AisClassAPositionReport(const Message &m) : Message(m) {};
    void setMessageId(unsigned char value) { Set(value,0,6); }
    unsigned char getMessageId() const { return Get(0,6); };
    void setRepeatIndicator(RepeatIndicator value) { Set((unsigned char)value,6,2); }
    RepeatIndicator getRepeatIndicator() const { return (RepeatIndicator)Get(6,2); };
    void setUserId(unsigned long value) { Set(value,8,32); }
    unsigned long getUserId() const { return Get(8,32); };
    void setLongitude(double value) { Set(value/1E-07,40,32); }
    double getLongitude() const { return 1E-07 * Get(40,32); };
    void setLatitude(double value) { Set(value/1E-07,72,32); }
    double getLatitude() const { return 1E-07 * Get(72,32); };
    void setPositionAccuracy(PositionAccuracy value) { Set((unsigned char)value,104,1); }
    PositionAccuracy getPositionAccuracy() const { return (PositionAccuracy)Get(104,1); };
    void setRaim(Raim value) { Set((unsigned char)value,105,1); }
    Raim getRaim() const { return (Raim)Get(105,1); };
    void setTimeStamp(TimeStamp value) { Set((unsigned char)value,106,6); }
    TimeStamp getTimeStamp() const { return (TimeStamp)Get(106,6); };
    void setCogRadians(double value) { Set(value/0.0001,112,16); }
    double getCogRadians() const { return 0.0001 * Get(112,16); }
    void setCogDegrees(double value) { Set(value/0.00572958,112,16); }
    double getCogDegrees() const { return 0.00572958 * Get(112,16); };
    void setSogMetersPerSecond(double value) { Set(value/0.01,128,16); }
    double getSogMetersPerSecond() const { return 0.01 * Get(128,16); }
    void setSogKnots(double value) { Set(value/0.0194384,128,16); }
    double getSogKnots() const { return 0.0194384 * Get(128,16); };
    void setCommunicationState(unsigned long value) { Set(value,144,19); }
    unsigned long getCommunicationState() const { return Get(144,19); };
    void setAisTransceiverInformation(AisTransceiverInformation value) { Set((unsigned char)value,163,5); }
    AisTransceiverInformation getAisTransceiverInformation() const { return (AisTransceiverInformation)Get(163,5); };
    void setHeadingRadians(double value) { Set(value/0.0001,168,16); }
    double getHeadingRadians() const { return 0.0001 * Get(168,16); }
    void setHeadingDegrees(double value) { Set(value/0.00572958,168,16); }
    double getHeadingDegrees() const { return 0.00572958 * Get(168,16); };
    void setRateOfTurn(double value) { Set(value/3.125E-05,184,16); }
    double getRateOfTurn() const { return 3.125E-05 * Get(184,16); };
    void setNavStatus(NavStatus value) { Set((unsigned char)value,200,4); }
    NavStatus getNavStatus() const { return (NavStatus)Get(200,4); };
    void setSpecialManeuverIndicator(SpecialManeuverIndicator value) { Set((unsigned char)value,204,2); }
    SpecialManeuverIndicator getSpecialManeuverIndicator() const { return (SpecialManeuverIndicator)Get(204,2); };
    void setAisSpare(unsigned char value) { Set(value,208,3); }
    unsigned char getAisSpare() const { return Get(208,3); };
    void setSequenceId(unsigned char value) { Set(value,216,8); }
    unsigned char getSequenceId() const { return Get(216,8); };
    static const pgn_t PGN = 129038;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() const { return PGN; }
  };
}
