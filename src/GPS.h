#ifndef  ARDU_APRS_TRACKER_GPS_H
#define  ARDU_APRS_TRACKER_GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define TIME_WAIT_DATA 1000

class GPS {
public:
    explicit GPS(byte rxPin, int baud = 9600, byte txPin = 0);

    bool getData();

    void displayInfo();

    TinyGPSPlus gps;
private:
    SoftwareSerial *serial;

    int baud;
};


#endif // ARDU_APRS_TRACKER_GPS_H
