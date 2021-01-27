#include <stdint.h>
#include "annepro2.h"
#include "led.h"
#include "ble.h"

/*
enum unicode_names {
    UCC_a,
    UCC_A,
    UCC_i,
    UCC_I,
    UCC_e,
    UCC_E,
    UCC_o,
    UCC_O,
    UCC_oo,
    UCC_OO,
    UCC_ooo,
    UCC_OOO,
    UCC_u,
    UCC_U,
    UCC_uu,
    UCC_UU,
    UCC_uuu,
    UCC_UUU
};

const uint32_t PROGMEM unicode_map[] = {
    [UCC_a] = 0xE1,
    [UCC_A] = 0xC1,
    [UCC_i] = 0xED,
    [UCC_I] = 0xCD,
    [UCC_e] = 0xE9,
    [UCC_E] = 0xC9,
    [UCC_o] = 0xF3,
    [UCC_O] = 0xD3,
    [UCC_oo] = 0xF6,
    [UCC_OO] = 0xD6,
    [UCC_ooo] = 0x151,
    [UCC_OOO] = 0x150,
    [UCC_u] = 0xFA,
    [UCC_U] = 0xDA,
    [UCC_uu] = 0xFC,
    [UCC_UU] = 0xDC,
    [UCC_uuu] = 0x171,
    [UCC_UUU] = 0x170
};

 [_UNICODE_LAYER] = KEYMAP(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, XP(UCC_e, UCC_E), KC_TRNS, KC_TRNS, KC_TRNS, XP(UCC_u, UCC_U), XP(UCC_i, UCC_I), XP(UCC_o, UCC_O), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, XP(UCC_a, UCC_A), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(UCC_uuu, UCC_UUU), XP(UCC_uu, UCC_UU), KC_TRNS, XP(UCC_oo, UCC_OO), XP(UCC_ooo, UCC_OOO), KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),
*/

enum custom_keys {
    KC_BT1_CONN = AP2_SAFE_RANGE,
    KC_BT2_CONN,
    KC_BT3_CONN,
    KC_BT4_CONN,
    KC_BT1_BROAD,
    KC_BT2_BROAD,
    KC_BT3_BROAD,
    KC_BT4_BROAD,

    KC_LED_BATTERY,
    KC_LED_TOGGLE,
    KC_LED_BRIGHT_DOWN,
    KC_LED_BRIGHT_UP,
    KC_GAMING_OFF,
    KC_LED_NEXT_PROFILE,
    KC_BT_UNPAIR,
    KC_USB
};


enum anne_pro_layers {
  _BASE_LAYER,
  //_UNICODE_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _GAMING_ARROW_LAYER,
  _GAMING_NUMPAD_LAYER
};


const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    LT(_FN1_LAYER, KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, LT(_FN1_LAYER, KC_LEFT), RCTL_T(KC_DOWN), LT(_FN2_LAYER, KC_RGHT)
 ),

 [_FN1_LAYER] = KEYMAP(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEAD, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),


 [_FN2_LAYER] = KEYMAP(
    KC_USB, KC_BT1_CONN, KC_BT2_CONN, KC_BT3_CONN, KC_BT4_CONN, KC_BT1_BROAD, KC_BT2_BROAD, KC_BT3_BROAD, KC_BT4_BROAD, KC_LED_TOGGLE, KC_LED_NEXT_PROFILE, KC_LED_BRIGHT_DOWN, KC_LED_BRIGHT_UP, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GAMING_OFF, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),


 [_GAMING_ARROW_LAYER] = KEYMAP(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER), KC_LEFT, KC_DOWN, KC_RGHT
 ),


 [_GAMING_NUMPAD_LAYER] = KEYMAP(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_8,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER), KC_KP_4, KC_KP_5, KC_KP_6
 ),
};

const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

static void executeLock(void);
static void toggleLock(void);
static void setNumpadOn(uint8_t led_state);

LEADER_EXTERNS();

void matrix_scan_user(void) {
    ble_read_data();
    
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();


        SEQ_THREE_KEYS(KC_A, KC_I, KC_F) {
            toggleLock();
        }

        SEQ_TWO_KEYS(KC_G, KC_A) {
            layer_off(_GAMING_NUMPAD_LAYER);
            layer_on(_GAMING_ARROW_LAYER);
            ledGamingOn();
        }

        SEQ_TWO_KEYS(KC_G, KC_N) {
            layer_off(_GAMING_ARROW_LAYER);
            layer_on(_GAMING_NUMPAD_LAYER);
            setNumpadOn(host_keyboard_leds());
            ledGamingOn();

            led_update_user(host_keyboard_led_state());
        }
    }
    
}


/*
    @brief Turns on num pad in case it is turned off.
*/
static void setNumpadOn(uint8_t led_state) {
    // Keeps Numpad turned on while _GAMING_NUMPAD_LAYER is on.
    if (layer_state_is(_GAMING_NUMPAD_LAYER) && !(led_state & (1<<USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
}

void led_set_user(uint8_t led_state) {
    setNumpadOn(led_state);

    // Update caps lock led.
    if (led_state & (1<<USB_LED_CAPS_LOCK)) {
        ledCapsOn();
    }
    else {
        ledCapsOff();
    }
}


//// EEPROM ////
#include "eeprom_w25x20cl.h"

static host_driver_t* driver;


#define MAGIC_CODE 0xE2

typedef struct {
    uint8_t magic : 8;
    uint8_t leds_on : 8;
    uint8_t leds_profile : 8;
    uint8_t locked : 8;
    uint8_t brightness : 8;
} user_config_t;

// define out default user_config
user_config_t user_config = {
    .magic = MAGIC_CODE, 
    .leds_on = 0, 
    .leds_profile = 0, 
    .locked = 0, 
    .brightness = 100};

// keep the number of profiles so we can track along with the shine proc
uint8_t numProfiles = 0;

static void saveConfig(void) {
    eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    
    
    if (record->event.pressed) {
        uint8_t keyPos = 0;
        keyPos |= (record->event.key.col << 4);
        keyPos |= record->event.key.row;
        ledKeyPressed(keyPos);
    }

    if (record->event.pressed && !user_config.locked) {
        switch (keycode) {
        case KC_LED_TOGGLE:
            ledToggle();
            user_config.leds_on = !user_config.leds_on;
            saveConfig();
            return false;

        case KC_LED_NEXT_PROFILE:
            ledNextProfile();
            user_config.leds_profile = (user_config.leds_profile + 1) % numProfiles;
            ledSetProfile(user_config.leds_profile);
            saveConfig();
            return false;

        case KC_BT1_CONN:
            ble_connect(0);
            return false;

        case KC_BT2_CONN:
            ble_connect(1);
            return false;

        case KC_BT3_CONN:
            ble_connect(2);
            return false;

        case KC_BT4_CONN:
            ble_connect(3);
            return false;

        case KC_BT1_BROAD:
            ble_broadcast(0);
            return false;

        case KC_BT2_BROAD:
            ble_broadcast(1);
            return false;

        case KC_BT3_BROAD:
            ble_broadcast(2);
            return false;

        case KC_BT4_BROAD:
            ble_broadcast(3);
            return false;

        case KC_USB:
            ble_disconnect();
            return false;

        case KC_BT_UNPAIR:
            ble_unpair();
            return false;

        case KC_LED_BRIGHT_DOWN:
            ledBrightDown();
            user_config.brightness = ledGetBrightness();
            saveConfig();
            break;

        case KC_LED_BRIGHT_UP:
            ledBrightUp();
            user_config.brightness = ledGetBrightness();
            saveConfig();
            break;

        case KC_GAMING_OFF:
            layer_off(_GAMING_NUMPAD_LAYER);
            layer_off(_GAMING_ARROW_LAYER);
            ledGamingOff();

        default:
            break;
        }
    }
    
    return true;
}

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    eeprom_read((void*)&user_config, 0, sizeof(user_config_t));

    // initialize a new eeprom
    //if (user_config.magic != MAGIC_CODE) {
        user_config.magic = MAGIC_CODE;
        user_config.leds_on = true;
        user_config.leds_profile = 0;
        user_config.locked = 0;
        saveConfig();
    //}

    ledSetProfile(user_config.leds_profile);

    if (user_config.leds_on) {
        ledToggle();
    }

    numProfiles = ledGetNumProfiles();

    ledSetBrightness(user_config.brightness);

    driver = host_get_driver();
    executeLock();
}

static void executeLock() {
    if (user_config.locked) {
        driver = host_get_driver();
        host_set_driver(0);
    } else {
        host_set_driver(driver);
    }
}

static void toggleLock() {
    user_config.locked = !(user_config.locked);
    executeLock();
    saveConfig();
}
