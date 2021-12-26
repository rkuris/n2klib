// class AisClassBPositionReport

// Automatically generated by mkmsgs - DO NOT EDIT
// Description: AIS Class B Position Report
#include "../n2k.h"
namespace n2k {
  class AisClassBPositionReport : public Message {
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

    enum class UnitType:unsigned char {
      SOTDMA = 0,
      CS = 1
    };

    enum class IntegratedDisplay:unsigned char {
      No = 0,
      Yes = 1
    };

    enum class Dsc:unsigned char {
      No = 0,
      Yes = 1
    };

    enum class Band:unsigned char {
      top_525_kHz_of_marine_band = 0,
      entire_marine_band = 1
    };

    enum class CanHandleMsg22:unsigned char {
      No = 0,
      Yes = 1
    };

    enum class AisMode:unsigned char {
      Autonomous = 0,
      Assigned = 1
    };

    enum class AisCommunicationState:unsigned char {
      SOTDMA = 0,
      ITDMA = 1
    };

    AisClassBPositionReport() {};
    AisClassBPositionReport(const Message &m) : Message(m) {};
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
    void setRegionalApplication(unsigned char value) { Set(value,184,8); }
    unsigned char getRegionalApplication() const { return Get(184,8); };
    void setRegionalApplication_1(unsigned char value) { Set(value,192,2); }
    unsigned char getRegionalApplication_1() const { return Get(192,2); };
    void setUnitType(UnitType value) { Set((unsigned char)value,194,1); }
    UnitType getUnitType() const { return (UnitType)Get(194,1); };
    void setIntegratedDisplay(IntegratedDisplay value) { Set((unsigned char)value,195,1); }
    IntegratedDisplay getIntegratedDisplay() const { return (IntegratedDisplay)Get(195,1); };
    void setDsc(Dsc value) { Set((unsigned char)value,196,1); }
    Dsc getDsc() const { return (Dsc)Get(196,1); };
    void setBand(Band value) { Set((unsigned char)value,197,1); }
    Band getBand() const { return (Band)Get(197,1); };
    void setCanHandleMsg22(CanHandleMsg22 value) { Set((unsigned char)value,198,1); }
    CanHandleMsg22 getCanHandleMsg22() const { return (CanHandleMsg22)Get(198,1); };
    void setAisMode(AisMode value) { Set((unsigned char)value,199,1); }
    AisMode getAisMode() const { return (AisMode)Get(199,1); };
    void setAisCommunicationState(AisCommunicationState value) { Set((unsigned char)value,200,1); }
    AisCommunicationState getAisCommunicationState() const { return (AisCommunicationState)Get(200,1); };
    static const pgn_t PGN = 129039;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() const { return PGN; }
  };
}
