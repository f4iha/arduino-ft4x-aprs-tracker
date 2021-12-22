#ifndef ARDU_APRS_TRACKER_UTILS_H
#define ARDU_APRS_TRACKER_UTILS_H

#ifdef TEST
#define IS_TEST_MODE true
#else
#define IS_TEST_MODE false
#endif

void blink(byte nb, int pinLedBlink = -1, int delayms = 250);
void blinkAll(byte nb, int pinLedBlink = -1, int delayms = 250, int maxStepMark=3);

#endif //ARDU_APRS_TRACKER_UTILS_H