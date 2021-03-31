#include "persistence.h"

#include "led.h"


/* 
 * STATIC DEFINITIONS 
 */

// define out default user_config
static user_config_t user_config = {
    .magic = MAGIC_CODE, 
    .leds_on = 0, 
    .leds_profile = 0, 
    .locked = 0, 
    .brightness = 100 
    };

// keep the number of profiles so we can track along with the led mcu
static int8_t numProfiles = 0;

static host_driver_t* driver;


static void saveConfig(void) {
    eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
}


static void executeLock(void) {
    ledSetLocked(user_config.locked);
    
    if (user_config.locked) {
        driver = host_get_driver();
        host_set_driver(0);
    } else {
        host_set_driver(driver);
    }
}


/* 
 * GLOBAL FUNCTIONS 
 */

void pers_init() {
    // Read the user config from EEPROM
    eeprom_read((void*)&user_config, 0, sizeof(user_config_t));

    // initialize a new eeprom
    if (user_config.magic != MAGIC_CODE) {
        user_config.magic = MAGIC_CODE;
        user_config.leds_on = false;
        user_config.leds_profile = 0;
        user_config.locked = 0;
        saveConfig();
    }

    ledSetProfile(user_config.leds_profile);

    if (user_config.leds_on) {
        ledToggle();
    }

    numProfiles = ledGetNumProfiles();

    ledSetBrightness(user_config.brightness);

    driver = host_get_driver();
    executeLock();
}

void pers_tick() {
    if (driver == 0 && user_config.locked) {
        driver = host_get_driver();
        host_set_driver(0);
    }
}

void pers_toggleLock() {
    user_config.locked = !(user_config.locked);
    executeLock();
    saveConfig();
}

bool pers_isLocked(void) {
    return user_config.locked;
}

void pers_ledToggle() {
    ledToggle();
    user_config.leds_on = !user_config.leds_on;
    saveConfig();
}

void pers_ledNextProf() {
    user_config.leds_profile = (user_config.leds_profile + 1) % numProfiles;
    ledSetProfile(user_config.leds_profile);
    saveConfig();
}

void pers_ledPrevProf() {
    user_config.leds_profile = ((int)user_config.leds_profile - 1) % numProfiles;
    ledSetProfile(user_config.leds_profile);
    saveConfig();
}

void pers_ledBrightUp() {
    ledBrightUp();
    user_config.brightness = ledGetBrightness();
    saveConfig();
}

void pers_ledBrightDown() {
    ledBrightDown();
    user_config.brightness = ledGetBrightness();
    saveConfig();
}

