
#include "led.h"

#include "hal.h"
#include "annepro2.h"



void ledToggle(void) {
  sdPut(&SD0, LED_TOGGLE);
}

void ledSetProfile(uint8_t profile) {
  sdPut(&SD0, LED_SET_PROFILE);
  sdPut(&SD0, profile);
}

uint8_t ledGetProfile(void) {
  uint8_t buf = 0;
  sdPut(&SD0, LED_GET_PROFILE);
  buf = sdGet(&SD0);
  return buf;
}

uint8_t ledGetNumProfiles(void) {
  uint8_t profileCount = 0;
  sdPut(&SD0, LED_GET_PROFILE_COUNT);
  profileCount = sdGet(&SD0);
  return profileCount;
}

void ledNextProfile(void) {
  sdPut(&SD0, LED_NEXT_PROFILE);
}

void ledKeyPressed(uint8_t keyPos) {
  sdPut(&SD0, LED_KEY_PRESSED);
  sdPut(&SD0, keyPos);
}

void ledBrightDown(void) {
  sdPut(&SD0, LED_BRIGHT_DOWN);
}

void ledBrightUp(void) {
  sdPut(&SD0, LED_BRIGHT_UP);
}

void ledCapsOn(void) {
  sdPut(&SD0, LED_CAPS_ON);
}

void ledCapsOff(void) {
  sdPut(&SD0, LED_CAPS_OFF);
}


void ledSetBrightness(uint8_t brightness) {
  sdPut(&SD0, LED_SET_BRIGHT);
  sdPut(&SD0, brightness);
}

uint8_t ledGetBrightness(void) {
  uint8_t brightness = 0;
  sdPut(&SD0, LED_GET_BRIGHT);
  brightness = sdGet(&SD0);
  return brightness;
}

void ledGamingOn(void) {
    sdPut(&SD0, LED_GAMING_ON);
}

void ledGamingOff(void) {
    sdPut(&SD0, LED_GAMING_OFF);
}

void ledBleConnecting(uint8_t port) {
    sdPut(&SD0, LED_BLT_CONNECTING);
    sdPut(&SD0, port);
}

void ledBleConnected(void) {
  sdPut(&SD0, LED_BLT_CONNECTED);
}

void ledSetLocked(bool isLocked) {
    sdPut(&SD0, LED_SET_LOCKED);
    sdPut(&SD0, isLocked);
}
