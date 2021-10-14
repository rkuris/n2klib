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
    unsigned char getMessageId() { return Get(0,6); };
    RepeatIndicator getRepeatIndicator() { return (RepeatIndicator)Get(6,2); };
    double getUserId() const { return 1 * Get(8,32); };
    double getLongitude() const { return 1E-07 * Get(40,32); };
    double getLatitude() const { return 1E-07 * Get(72,32); };
    PositionAccuracy getPositionAccuracy() { return (PositionAccuracy)Get(104,1); };
    Raim getRaim() { return (Raim)Get(105,1); };
    TimeStamp getTimeStamp() { return (TimeStamp)Get(106,6); };
    double getCog() const { return 0.00572958 * Get(112,16); };
    double getSog() const { return 0.0194384 * Get(128,16); };
    unsigned long getCommunicationState() { return Get(144,19); };
    AisTransceiverInformation getAisTransceiverInformation() { return (AisTransceiverInformation)Get(163,5); };
    double getHeading() const { return 0.00572958 * Get(168,16); };
    unsigned char getRegionalApplication() { return Get(184,8); };
    unsigned char getRegionalApplication() { return Get(192,2); };
    UnitType getUnitType() { return (UnitType)Get(194,1); };
    IntegratedDisplay getIntegratedDisplay() { return (IntegratedDisplay)Get(195,1); };
    Dsc getDsc() { return (Dsc)Get(196,1); };
    Band getBand() { return (Band)Get(197,1); };
    CanHandleMsg22 getCanHandleMsg22() { return (CanHandleMsg22)Get(198,1); };
    AisMode getAisMode() { return (AisMode)Get(199,1); };
    AisCommunicationState getAisCommunicationState() { return (AisCommunicationState)Get(200,1); };
    static const pgn_t PGN = 129039;
    static const PGNType Type = PGNType::Fast;
    pgn_t getPGN() { return PGN; }
  };
}
