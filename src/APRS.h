#ifndef ARDU_APRS_TRACKER_APRS_H
#define ARDU_APRS_TRACKER_APRS_H

#include <Arduino.h>
#include "GPS.h"

class APRS {
public:
    APRS(GPS *gps, uint8_t txPin);

    void init(char *call, uint8_t callId, char *toCall, uint8_t toCallId, char *relays);

    bool sendIfPossible(bool forceGps = false, bool forceTx = false, int selectedBlinkPin = LED_BUILTIN);

    void setComment(String comment);

    void setSymbol(char symbol);

private:
    GPS *gps = nullptr;

    uint8_t lastSpeed = 0;
    uint64_t lastTx = 0;
    uint8_t txPin = 0;

    String packetBuffer;
    String comment;
    char symbol;

    long readVccAtmega();
    uint16_t getTimeSecondsForGivenSpeed();

    float convertDegMin(float decDeg);
    void stringPadding(int number, byte width, String *dest);
    void stringPaddingf(float number, byte width, String *dest);

    void buildPacket();
    bool txToRadio();
    bool sendPosition();
    void print_uint64_t(uint64_t num);
};


#endif //ARDU_APRS_TRACKER_APRS_H
