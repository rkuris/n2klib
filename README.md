# n2klib

Unsatisifed with the size and quality of the NMEA 2000
libraries out there to interface with CAN, I decided to
do a fresh start. The things I am after:

 - Classes for each message. Since most of the time,
   applications only care about a few NMEA 2000 messages,
   I don't want all the code to encode or decode all of
   them, so they get built into separate files. If your
   code references them, they will be pulled in, otherwise
   not.
 - Autogeneration. Classes should be generated from
   a DSL or another definition file, reducing the chance
   of a coding error on a particular message type.
 - Tests. I am a firm believer that the tests shouldn't
   need access to a CANbus. There should be unit tests
   that prove that each case works correctly.
 - Support for variable length stuff. Most of the libraries
   I saw didn't support things like a set of satellites
   in a message.
