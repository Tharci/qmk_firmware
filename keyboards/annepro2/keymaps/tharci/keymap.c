#include <stdint.h>
#include "annepro2.h"
#include "led.h"
#include "ble.h"
#include "hid_comm.h"
#include "persistence.h"
#include "raw_hid.h"

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

static void goIntoIAP(void);



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
    KC_LED_PREV_PROFILE,
    KC_BT_UNPAIR,
    KC_USB,
    KC_IAP_MODE,
};


// Tap Dance declarations
enum {
    TD_BLT_1,
    TD_BLT_2,
    TD_BLT_3,
    TD_BLT_4,
};

void td_blt(unsigned count, uint8_t bleId) {
    if (count == 1) {
        ble_connect(bleId);
    }
    else if(count == 2) {
        ble_broadcast(bleId);
    }
}

void td_blt_1(qk_tap_dance_state_t *state, void *user_data) {
    td_blt(state->count, 0);
}

void td_blt_2(qk_tap_dance_state_t *state, void *user_data) {
    td_blt(state->count, 1);
}

void td_blt_3(qk_tap_dance_state_t *state, void *user_data) {
    td_blt(state->count, 2);
}

void td_blt_4(qk_tap_dance_state_t *state, void *user_data) {
    td_blt(state->count, 3);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_BLT_1] = ACTION_TAP_DANCE_FN(td_blt_1),
    [TD_BLT_2] = ACTION_TAP_DANCE_FN(td_blt_2),
    [TD_BLT_3] = ACTION_TAP_DANCE_FN(td_blt_3),
    [TD_BLT_4] = ACTION_TAP_DANCE_FN(td_blt_4)
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
    KC_TRNS, KC_VOLU, KC_MNXT, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_VOLD, KC_MPRV, KC_BRID, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_MUTE, KC_MPLY, KC_CALC, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEAD, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),


 [_FN2_LAYER] = KEYMAP(
    KC_USB, TD(TD_BLT_1), TD(TD_BLT_2), TD(TD_BLT_3), TD(TD_BLT_4), KC_TRNS, KC_TRNS, KC_TRNS, KC_LED_TOGGLE, KC_LED_PREV_PROFILE, KC_LED_NEXT_PROFILE, KC_LED_BRIGHT_DOWN, KC_LED_BRIGHT_UP, KC_TRNS,
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


PowerPlan powerPlan = POWER_SAVING;


void matrix_init_user(void) {

}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

static void executeLock(void);
static void setNumpadOn(uint8_t led_state);

LEADER_EXTERNS();

void matrix_scan_user(void) {
    ble_read_data();
    
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // TOGGLE LOCK
        SEQ_THREE_KEYS(KC_A, KC_I, KC_F) {
            pers_toggleLock();
        } 

        // TURN ON GAMING MODE - ARROWS
        SEQ_TWO_KEYS(KC_G, KC_A) {
            layer_off(_GAMING_NUMPAD_LAYER);
            layer_on(_GAMING_ARROW_LAYER);
            ledGamingOn();
        }

        // TURN ON GAMING MODE - NUMPAD
        SEQ_TWO_KEYS(KC_G, KC_N) {
            layer_off(_GAMING_ARROW_LAYER);
            layer_on(_GAMING_NUMPAD_LAYER);
            setNumpadOn(host_keyboard_leds());
            ledGamingOn();

            led_update_user(host_keyboard_led_state());
        }

        // IAP MODE
        SEQ_THREE_KEYS(KC_I, KC_A, KC_P) {
            goIntoIAP();
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


void raw_hid_receive(uint8_t *data, uint8_t length) {
    hid_handle(data, length);
}



static void goIntoIAP(void) {
    ledGoIntoIAP();
    // wait for shine to go into IAP mode
    wait_ms(15);

    // Magic key to set keyboard to IAP
    *((uint32_t*)0x20001ffc) = 0x0000fab2;

    __disable_irq();
    NVIC_SystemReset();
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    pers_tick();

    if (record->event.pressed) {
        uint8_t keyPos = 0;
        keyPos |= (record->event.key.col << 4);
        keyPos |= record->event.key.row;
        ledKeyPressed(keyPos);
    }

    if (record->event.pressed && !pers_isLocked()) {
        switch (keycode) {
        case KC_LED_TOGGLE:
            pers_ledToggle();
            return false;

        case KC_LED_NEXT_PROFILE:
            pers_ledNextProf();
            return false;

        case KC_LED_PREV_PROFILE:
            pers_ledPrevProf();
            return false;

        case KC_USB:
            ble_disconnect();
            return false;

        case KC_BT_UNPAIR:
            ble_unpair();
            return false;

        case KC_LED_BRIGHT_UP:
            pers_ledBrightUp();
            return false;

        case KC_LED_BRIGHT_DOWN:
            pers_ledBrightDown();
            return false;

        case KC_GAMING_OFF:
            layer_off(_GAMING_NUMPAD_LAYER);
            layer_off(_GAMING_ARROW_LAYER);
            ledGamingOff();
            return false;

        case KC_IAP_MODE:
            goIntoIAP();
            return false;

        default:
            break;
        }
    }
    
    return true;
}


void keyboard_post_init_user(void) {
    pers_init();

    ledSetPowerPlan(powerPlan);
}
