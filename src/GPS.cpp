#include "GPS.h"
#include "Utils.h"

GPS::GPS(byte rxPin, int baud, byte txPin) : baud(baud) {
    serial = new SoftwareSerial(rxPin, txPin);
}

bool GPS::getData() {
    Serial.println("GPS update...");

    serial->begin(baud);
    uint32_t start = millis();
    do {
        while (serial->available()) {
            char r = (char) serial->read();
            //Serial.print(r);   
            gps.encode(r);
        }
    } while (millis() - start < TIME_WAIT_DATA);
    serial->flush();
    serial->end();

    if (!gps.location.isValid()) {
        Serial.print("GPS no fix, sat: "); 
        Serial.println(gps.satellites.value());
        return false;
    }
    Serial.println("GPS OK");
    displayInfo();
    return true;
}


void GPS::displayInfo() {
    Serial.print("Sat: "); Serial.print(gps.satellites.value());
    Serial.print(" HDOP: "); Serial.println(gps.hdop.hdop(), 0);

    Serial.print("Lat: "); Serial.println(gps.location.lat(), 6);
    Serial.print("Lng: "); Serial.println(gps.location.lng(), 6);

    Serial.print("Alt: "); Serial.print(gps.altitude.meters(), 0);
    Serial.print(" Spd: "); Serial.print(gps.speed.kmph(), 0);
    Serial.print(" Crs: "); Serial.println(gps.course.deg(), 0);

}
