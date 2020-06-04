#include <stdio.h>
#include <linux/can.h>
#include <assert.h>

typedef unsigned char prio_t;	// a priority (0-7)
typedef unsigned long pgn_t;	// a pgn
typedef unsigned char addr_t;   // src or destination

#define CAN_BROADCAST_ADDR ((addr_t)0xff)

inline prio_t getPriority(const canid_t id) {
	return (prio_t)((id>>26) & 7);
}
inline void setPriority(canid_t &id, const prio_t priority) {
	id |= (((canid_t)priority&7)<<26);
}
inline pgn_t getPGN(const canid_t id) {
	unsigned char hi = id>>16;
	unsigned char datapage = (id>>24)&1;
	if (hi < 240) {
		// PDU1 format
		return (datapage<<16) + (hi << 8);
	}
	unsigned char lo = id>>8;
	return (datapage<<16) + (hi << 8) + lo;
}
inline void setPGN(canid_t &id, pgn_t pgn) {
	unsigned char hi = pgn >> 8;
	if (hi < 240) {
		// PDU1 format
		id |= (((canid_t)pgn) << 8) & 0xff0000;
		return;
	}
	id |= ((canid_t)pgn) << 8;
}
inline addr_t getSource(const canid_t id) {
	return (addr_t)id;	
}
inline void setSource(canid_t &id, const addr_t source) {
	id |= source;
}

inline addr_t getDestination(const canid_t id) {
	unsigned char hi = id>>16;
	if (hi < 240) {
		// PDU1 format has a destination
		return id >> 8;
	}
	return CAN_BROADCAST_ADDR;
}

inline void setDestination(canid_t &id, const addr_t dest) {
	id |= (canid_t)dest << 8;
}
