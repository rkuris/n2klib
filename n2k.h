/*!
 * \file n2k.h
 * \brief Core n2k functionality
 *
 * You'll need this include first when working with
 * this library.
 */
#pragma once

#include <assert.h>
#include <functional>
#include <vector>
#include <cstring>

#include "./intmem/intmem.h"

namespace n2k
{
  typedef unsigned long canid_t;	// a CANbus identifier
  typedef unsigned char prio_t;	// a priority (0-7)
  typedef unsigned long pgn_t;	// a pgn
  typedef unsigned char addr_t;	// src or destination
  // Only certain PGNs have a destination
  const addr_t CAN_BROADCAST_ADDR = 0xff;
  const canid_t EFF_FRAME = 0x80000000U;
  inline bool pgnIsAlwaysBroadcast(pgn_t pgn) {
	  return pgn < 65536;
  }


  /*! PGNType is either SINGLE_PACKET or FAST_PACKET
   *  Most packets are FAST_PACKET type, which consist
   *  of multiple packets for the whole message
   */
  enum class PGNType
  {
    Single,
    Fast,
  };

  /*! \brief 8-byte packet (frame)
   *
   * Contains a single 8 byte packet that fits on the canbus
   * TODO: Rename this to Frame since that's the term used
   * on the canbus.
   */
  class Packet
  {
  public:
    static const int MAX_CAN_DATA = 8;

    Packet() : canid{0} {}
    Packet(unsigned char *data_) : canid{0} {
	    memcpy(data, data_, MAX_CAN_DATA);
    }
    Packet(pgn_t pgn, prio_t priority, addr_t source, unsigned char *data_) : canid{0} {
	    setPGN(pgn);
	    setPriority(priority);
	    if (!pgnIsAlwaysBroadcast(pgn)) {
		    setSource(source);
	    }
	    memcpy(data, data_, MAX_CAN_DATA);
    }

    canid_t canid;
    unsigned char data[MAX_CAN_DATA];	// TODO: Can we make these pointers?
  /*! getPriority fetches the priority from a canid
   */
  inline prio_t getPriority () const
  {
    return (prio_t) ((canid >> 26) & 7);
  }

  /*! setPriority sets the priority bits in a canid
   *
   * NOTE: the bits are not cleared; it's assumed
   * we are constructing from a zeroed id
   */
  inline void setPriority (const prio_t priority)
  {
    canid |= (((canid_t) priority & 7) << 26);
  }

  /*! getPGN fetches the PGN (Parameter Group Number)
   * embedded in a canid
   */
  inline pgn_t getPGN () const
  {
    unsigned char hi = canid >> 16;
    unsigned char datapage = (canid >> 24) & 1;
    if (hi < 240)
      {
	// PDU1 format
	return (datapage << 16) + (hi << 8);
      }
    unsigned char lo = canid >> 8;
    return (datapage << 16) + (hi << 8) + lo;
  }

  /*! setPGN sets the PGN in a canid
   *
   * NOTE: the bits are not cleared; it's assumed
   * we are constructing from a zeroed id
   */
  inline void setPGN (pgn_t pgn)
  {
    canid |= pgn&0xff;
    canid |= EFF_FRAME;
    unsigned char hi = pgn >> 8;
    if (hi < 240)
      {
	// PDU1 format
	canid |= (((canid_t) pgn) << 8);
	return;
      }
    canid |= ((canid_t) pgn) << 8;
  }

  /*! getSource fetches the source address from a canid
   */
  inline addr_t getSource () const
  {
    return (addr_t) canid;
  }

  /*! setSource sets the source address for a canid
   */
  inline void setSource (const addr_t source)
  {
    canid |= source;
  }

  /*! getDestination fetches the destination address
   *  from a given canid. For most messages, this is
   *  the CAN_BROADCAST_ADDR of 0xff (255).
   */
  inline addr_t getDestination () const
  {
    unsigned char hi = canid >> 16;
    if (hi < 240)
      {
	// PDU1 format has a destination
	return canid >> 8;
      }
    return CAN_BROADCAST_ADDR;
  }

  /*! setDestination sets the destination address
   * for a given message. You should ONLY call this
   * on messages that have a destination; most do not
   */
  inline void setDestination (const addr_t dest)
  {
    canid |= (canid_t) dest << 8;
  }

  };

  /*!
   * \brief Contains a single NMEA 2000 message.
   *
   * Message is a class containing a single NMEA message.
   * These can be assembled from Packet classes, typically
   * from the CAN bus, or transmitted by splitting them into
   * a stream of Packet classes.
   *
   * User's typically don't use this class directly, instead
   * they use a Transciever (or Receiver) class which has
   * a MessagePool used for assembling a Message from one or
   * more Packet classes, and a derived class for fetching
   * the fields of the Message by name. All the named NMEA2000
   * classes extend this.
   */
  class Message
  {
  public:
    static const int MAX_NMEA_DATA = 223;
    unsigned char data[MAX_NMEA_DATA];

    virtual pgn_t getPGN () const = 0;

    /** Set some bits in the data array
     *
     * @param value [in] the value to store
     * @param start [in] the starting bit where the data begins
     * @param len   [in] the length, in bits, of the data
     *
     */
    template <class T>
    void Set (T value, int start, int len)
    {
      unsigned char startbit = start % 8;
      unsigned char startbyte = start / 8;
      if (startbit == 0)
	{
	  switch (len)
	    {
	    case 8:
	      data[startbyte] = (unsigned char)value;
	      return;
	    case 16:
	      intmem::storeu_le<uint16_t>(data + startbyte, value);
	      return;
	    case 32:
	      intmem::storeu_le<uint32_t>(data + startbyte, value);
	      return;
	    case 64:
	      intmem::storeu_le<uint64_t>(data + startbyte, value);
	      return;
	    }
	}
      abort(); // FIXME TODO
    }
    /** Get some bits from the data array into a long
     *
     * @param start [in] the starting bit where the data begins
     * @param len   [in] the length, in bits, of the data
     *
     * @return a long from the given set of bits
     */
    unsigned long Get (int start, int len) const
    {
      unsigned char startbit = start % 8;
      unsigned char startbyte = start / 8;
      // optimize for most common case, full bytes
      if (startbit == 0)
	{
	  switch (len)
	    {
	    case 8:
	      return data[startbyte];
	    case 16:
	      return intmem::loadu_le<uint16_t>(data + startbyte);
	    case 32:
	      return intmem::loadu_le<uint32_t>(data + startbyte);
	    case 64:
	      return intmem::loadu_le<uint64_t>(data + startbyte);
	    }
	}
      unsigned long result = 0;
      int remain = len;
      while (remain >= 8 && startbit == 0)
	{
	  result = (result << 8) + data[startbyte];
	  startbyte++;
	  remain -= 8;
	}
      while (remain > 0)
	{
	  result = result << 1;
	  result |= (data[startbyte] & (1 << startbit)) >> startbit;
	  startbit++;
	  if (startbit > 7)
	    {
	      startbit -= 8;
	      startbyte++;
	    }
	  remain--;
	}
      return result;
    }
  };

/*! PoolSizeType defines the data type for the 
 *
 */
  typedef unsigned short PoolSizeType;

  /*! \brief Message with state info
   *
   * Contains a Message along with state information
   * used while gathering portions of a packet
   *
   */
  class MessageWithState:public Message
  {
  public:
    unsigned short m_busy:1,	/* 1 indicates given to handler */
      m_next:5,			/* next packet expected sequence */
      m_last:5;			/* last packet sequence */
    pgn_t m_pgn;
    unsigned char m_age;
    virtual pgn_t getPGN () const { return m_pgn; }
  };

  /*! \brief Contains a set of Messages and states
   *
   * A MessagePool holds a set of Messages, along with
   * some metadata about each message state
   *
   * Packets are sometimes whole NMEA2000 messages,
   * but often they are just part of a message. In
   * the case of a partial message, the MessagePool
   * is used to hold the parts until a whole message
   * is fetched.
   *
   * Message objects managed by this class start off
   * with m_busy = 0
   */
  class MessagePool
  {
  public:
    static const PoolSizeType DEFAULT_POOL_SIZE = 5;

    /*! Construct a MessagePool of a given size.
     *
     * @param poolSize The size of the pool, in
     *                 number of messages. On low
     *                 memory machines, set this
     *                 below the default of 5. If
     *                 you have lots of memory, and
     *                 lots of talkers that send
     *                 partial messages, set this
     *                 higher, same as the number of
     *                 talkers (maybe 10 or 20).
     *                 Not sure? Use the default.
     *
     *                 The risk of having this too low
     *                 is that you might lose a packet.
     */
      MessagePool (const PoolSizeType poolSize = DEFAULT_POOL_SIZE)
    {
      for (int i = 0; i < poolSize; i++)
	{
	  mPool.push_back (MessageWithState ());
	}
    }

    /*! Ingest a packet, typically from the CAN bus.
     *
     * @param packet A reference to the Packet to ingest
     * @param type   The type of this packet (Single or Fast)
     *
     * @return If this completes a Message, then a pointer
     *         to the message is returned, otherwise nullptr.
     */
    MessageWithState *ingest (const Packet & packet, const PGNType type)
    {
      in++;
      switch (type)
	{
	case PGNType::Single:
	  {
	    // simple case, we always get a packet
	    MessageWithState & m = getFree ();
	    std::memcpy(m.data, packet.data, sizeof(packet.data));
	    m.m_pgn = packet.getPGN();
	    return &m;
	  }

	case PGNType::Fast:
	  auto order = packet.data[0] & kPacketMask;
	  auto pgn = packet.getPGN();
	  if (order == 0) {
		// first of set of packets
		MessageWithState & m = getFree ();
	        std::memcpy(m.data, packet.data + 2, sizeof(packet.data) - 2);
		m.m_next = 1;
		m.m_busy = 1;
		m.m_pgn = pgn;
		// The last packet is easy to compute
		//  N   D (data sizes)
		//  0   1-6
		//  1   7-13
		//  2   14-20
		// so we just divide by 7 and round down
		m.m_last = packet.data[1] / 7;
		return nullptr;
	  } else {
		MessageWithState *m = find(pgn);
		if (m == nullptr) {
			// couldn't find first packet
		       return nullptr;
		}
		if (order != m->m_next) {
			// wrong next packet
			m->m_busy = 0;
			return nullptr;
		}
	        std::memcpy(m->data + 6 + (order-1)*7, packet.data + 1, sizeof(packet.data) - 1);
		if (order == m->m_last) {
			// got it all
			return m;
		}
		// now look for next packet
		m->m_next++;
		return nullptr;
	  }
	}
      assert (false);		// oops, unknown type
    }

  protected:
    std::vector < MessageWithState > mPool;
    int in;
    int out;
    int discards;
    const int kPacketMask = 0x1f;

  private:
    MessageWithState * find(pgn_t pgn)
    {
      for (auto it = std::begin (mPool); it != std::end (mPool); ++it)
      {
	  if (it->m_busy == 0)
	     continue;
	  if (it->m_pgn == pgn)
	     return &*it;
      }
      // oops, we couldn't find it. This can happen at startup if
      // we see the back half of a packet
      return nullptr;
    }
    /*! \brief Get a free MessageWithState
     *
     * This method walks the list of items in the pool
     * and finds an entry that:
     *  - is not being assembled or handed to a callback (m_busy==0)
     *  - An entry that's been around for 256 messages and hasn't been
     *    completed (m_age overflowed)
     *  - The oldest message (largest m_age)
     */
    MessageWithState & getFree ()
    {
      MessageWithState *best = nullptr, *oldest = nullptr;

      for (auto it = std::begin (mPool); it != std::end (mPool); ++it)
	{
	  if (it->m_busy == 0)
	    {
	      best = &*it;
	    }
	  else
	    {
	      if (++(it->m_age) == 0)
		{
		  makeFree (*it);
		  best = &*it;
		}
	      else if ((oldest == nullptr) || (it->m_age > oldest->m_age))
		{
		  oldest = &*it;
		}
	    }
	}
      if (best != nullptr)
	{
	  best->m_busy = 1;
	  return *best;
	}
      // we couldn't find a free one, so nuke the oldest
      makeFree (*oldest);
      oldest->m_busy = 1;
      return *oldest;
    }

    /*! Make a MessageWithState free again
     *  subject to reassignment
     */
    void makeFree (MessageWithState & m)
    {
      m.m_age = 0;
      m.m_pgn = 0;
      m.m_busy = 0;
    }

  };

  /*! \typedef CallbackFunc
   *  \brief A std::function that takes a Message reference
   */
  using CallbackFunc = std::function < void (const Message & msg) >;

/*! \brief Holds a PGN and a callback function
 *       
 *  If the pgn matches, the callback is called, passing
 *  the Message class to the callback function
 *
 *  Vectors of these are passed around in CallbackList
 */
  class Callback
  {
  public:
    Callback (pgn_t pgn, PGNType pgntype, CallbackFunc callback)
    {
      mpgn = pgn;
      mpgntype = pgntype;
      mcallback = callback;
    };
    pgn_t mpgn;
    PGNType mpgntype;
    CallbackFunc mcallback;
  };

  /*! \brief A vector of callbacks
   */
  class CallbackList
  {
  public:
    std::vector < Callback > mCallbacks;

    CallbackList ()
    {
    }
    CallbackList (Callback * callbacks, int n)
    {
      for (int i = 0; i < n; i++)
	{
	  mCallbacks.push_back (callbacks[i]);
	}
    };

    void addCallback (const Callback & cb)
    {
      mCallbacks.push_back (cb);
    }
  };


  /*! \brief Message assembler from Packet
   *
   * This class contains all the stuff needed to construct
   * N2k::Message objects from Packets. It expects for someone
   * to call Receiver::ingest on each received packet.
   */
  class Receiver
  {
  public:

    /*! The default constructor is usually fine unless you want to provide
     *  callbacks on instantiation or you want to change the size of
     *  the MessagePool
     */
    Receiver ():mPool (new MessagePool ()),
      mCallbackList (new CallbackList ())
    {
    }

    /*! Construct a receiver with a given message pool size. This is a
     *  convenience function so that callers with low memory can just call
     *  something like r=Receiver(2), then add their callbacks with
     *  r.addCallback(pgn, function)
     *
     *  @param size The pool size; see the MessagePool constructor for details
     */
    Receiver (PoolSizeType size):mPool (new MessagePool (size)),
      mCallbackList (new CallbackList ())
    {
    }

    /*! For total control, provide a MessagePool and a CallbackList
     *
     * @param pool The message pool
     * @param callbacks A CallbackList to set up the callbacks
     */
  Receiver (MessagePool * pool, CallbackList * callbacks):mPool (pool),
      mCallbackList
      (callbacks)
    {
    }

    /*! ingest inserts a packet into the appropriate Message in the
     *  MessagePool and calls the registered Callback. If there aren't
     *  any callbacks, this method does nothing.
     *
     *  Care is taken to call all the callbacks, allowing duplicates
     *  in the callback list.
     */
    void ingest (const Packet & packet)
    {
      // search for packet.canid in the callbacks
      MessageWithState *msg = nullptr;
      for (auto it = std::begin (mCallbackList->mCallbacks);
	   it != std::end (mCallbackList->mCallbacks); ++it)
	{
	  if (packet.getPGN () == it->mpgn)
	    {
	      // found matching callback; ingest the
	      // packet if we haven't already
	      if (msg == nullptr)
		{
		  msg = mPool->ingest (packet, it->mpgntype);
		  // if this packet doesn't complete a message,
		  // we're done for now
		  if (msg == nullptr)
		    {
		      return;
		    }
		}
	      // msg can't be a nullptr at this point
	      it->mcallback (*msg);
	    }
	}
        // callbacks all done, this message is now available
	// for reuse
        if (msg != nullptr) {
	    msg->m_busy = 0;
	}
    }
    void addCallback (const Callback & cb)
    {
      mCallbackList->addCallback (cb);
    }

  protected:
    MessagePool * mPool;
    CallbackList *mCallbackList;
  };
}
