#include <Arduino.h>

void blink(byte nb, int pinLedBlink, int delayms) {
    if (pinLedBlink > -1){
        for (byte i = 0; i < nb; i++) {
            digitalWrite(pinLedBlink, LOW);
            delay(delayms);
            digitalWrite(pinLedBlink, HIGH);
            delay(delayms);
        }
    }
}

void blinkAll(byte nb, int pinLedBlink, int delayms, int maxStepMark){
    if (pinLedBlink > -1){
        for (byte i = 0; i < nb; i++) {
            for (int tmpLed = pinLedBlink; tmpLed < (pinLedBlink + maxStepMark); tmpLed++){
                digitalWrite(pinLedBlink, LOW);
            }
            delay(delayms);
            for (int tmpLed = pinLedBlink; tmpLed < (pinLedBlink + maxStepMark); tmpLed++){
                digitalWrite(pinLedBlink, HIGH);
            }
            delay(delayms);
        }
    }  
}