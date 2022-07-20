#include <Arduino.h>
#include "Utils.h"
#include "GPS.h"
#include "APRS.h"
#include <EasyButton.h>

#define APRS_COMMENT " send from  https://github.com/f4iha/arduino-ft4x-aprs-tracker"
#define BUTTON_SELECT 2
#define BUTTON_VALID 3
#define TX_GPS 7 // from GPS to Arduino
#define PTT_OUT 12

char CALL[] = "CALLSIGN";
uint8_t callSsid = '9'; // car
char TO_CALL[] = "APFD01"; // AP = AP Packet + F = France + D01 = department 01 in France
uint8_t TO_CALL_ID = '0';
char RELAYS[]  = "WIDE1-1,WIDE2-2";
String aprsMarks[] = { "voiture", "velo", "pieton" };
char aprsTypes[] = ">b[";

bool isTestMode = IS_TEST_MODE;

bool valid_state = false;
int stepMark = 0;
int loopInitMode = 0;
int maxStepMark = 3;
int pinLed =4 ;
int selectedPin = pinLed;

GPS gps(TX_GPS);
APRS aprs(&gps, PTT_OUT);
EasyButton button_select(BUTTON_SELECT);
EasyButton button_valid(BUTTON_VALID);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ...");
    
    pinMode(BUTTON_SELECT, INPUT_PULLUP);  
    pinMode(BUTTON_VALID, INPUT_PULLUP); 

    for (int tmpLed = pinLed; tmpLed < (pinLed + maxStepMark); tmpLed++){
        pinMode(tmpLed,OUTPUT); 
    }

    button_select.begin();  
    button_valid.begin();
    
    button_valid.read();

    if (button_valid.isPressed()) {
        isTestMode = !isTestMode;
        Serial.println("Test mode: ");
        Serial.println(isTestMode);
    }

    aprs.init(CALL, callSsid, TO_CALL, TO_CALL_ID, RELAYS);
    aprs.setComment(APRS_COMMENT);
    aprs.setPinLed(pinLed);

    button_valid.onPressedFor(3000, []() {
        Serial.println("TX Forced");
        blink(5, selectedPin, 50);
        if (valid_state == true){
            aprs.sendIfPossible(isTestMode, true, selectedPin);
        }
    });

    digitalWrite(pinLed,HIGH);
}

void loop() {
    if(valid_state == false){
        button_valid.read();
        button_select.read();
        // if time spend in this selection mode around 20s, we activate with the first mode
        if(button_valid.isPressed() || loopInitMode > 100){
            valid_state = true;
            selectedPin = stepMark + pinLed;
            blink(10, selectedPin, 50);
            Serial.print("Selected ");
            Serial.println(aprsMarks[stepMark]);
            aprs.setSymbol(aprsTypes[stepMark]);
        }
        if(button_select.isPressed()){
            digitalWrite(stepMark+pinLed,LOW); 
            stepMark++;
            if (stepMark == maxStepMark){
                stepMark = 0;
            }
            Serial.print("Displaying ");
            Serial.println(aprsMarks[stepMark]);
            digitalWrite(stepMark+pinLed,HIGH); 
        }
        delay(200);
        loopInitMode++;
    } else {
        button_valid.read();
        aprs.sendIfPossible(isTestMode, isTestMode, selectedPin);     
    }
}
