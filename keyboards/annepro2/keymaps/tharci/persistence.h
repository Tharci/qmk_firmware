#ifndef PERSISTECE_H
#define PERSISTECE_H

#include "quantum.h"
#include "eeprom_w25x20cl.h"


#define MAGIC_CODE 0xE2

typedef struct {
    uint8_t magic : 8;
    uint8_t leds_on : 8;
    uint8_t leds_profile : 8;
    uint8_t locked : 8;
    uint8_t brightness : 8;
} user_config_t;


void pers_init(void);
void pers_tick(void);

void pers_toggleLock(void);
bool pers_isLocked(void);

void pers_ledToggle(void);
void pers_ledNextProf(void);
void pers_ledPrevProf(void);
void pers_ledBrightUp(void);
void pers_ledBrightDown(void);


#endif // PERSISTECE_H