/*
    Copyright (C) 2020 Yaotian Feng, Codetector<codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ble.h"

#include "ch.h"
#include "hal.h"
#include "host.h"
#include "host_driver.h"
#include "led.h"
#include "annepro2.h"

/* -------------------- Static Function Prototypes -------------------------- */
static uint8_t ble_leds(void);
static void ble_mouse(report_mouse_t *report);
static void ble_system(uint16_t data);
static void ble_consumer(uint16_t data);
static void ble_keyboard(report_keyboard_t *report);

static void swtich_ble_driver(void);

/* -------------------- Static Local Variables ------------------------------ */
static host_driver_t ble_driver = {
    ble_leds,
    ble_keyboard,
    ble_mouse,
    ble_system,
    ble_consumer,
};

static uint8_t bleMcuWakeup[11] = {
    0x7b, 0x10, 0x53, 0x10, 0x03, 0x00, 0x01, 0x7d, 0x02, 0x01, 0x02
};
static uint8_t bleMcuStartBroadcast[11] = {
    0x7b, 0x10, 0x53, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x01, 0x00 // Broadcast ID[0-3]
};
static uint8_t bleMcuConnect[11] = {
    0x7b, 0x10, 0x53, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x04, 0x00 // Connect ID [0-3]
};
static uint8_t bleMcuSendReport[10] = {
    0x7b, 0x10, 0x53, 0x10, 0x0A, 0x00, 0x00, 0x7d, 0x10, 0x04,
};
static uint8_t bleMcuUnpair[10] = {
    0x7b, 0x10, 0x53, 0x10, 0x02, 0x00, 0x00, 0x7d, 0x40, 0x05,
};

static host_driver_t *lastHostDriver = NULL;
#ifdef NKRO_ENABLE
static bool lastNkroStatus = false;
#endif // NKRO_ENABLE

static uint8_t ble_led_state = 0;
static bool ble_connecting = false;
static uint8_t ble_broadcasting = 0;

/* -------------------- Public Function Implementation ---------------------- */

void ble_startup(void) {
    sdWrite(&SD1, bleMcuWakeup, 11);
}


void ble_broadcast(uint8_t port) {
    ledBleConnecting(port + 1 + 4);
    ble_broadcasting = port + 1;

    if (port > 3) {
        port = 3;
    }
    sdPut(&SD1, 0x00);
    sdWrite(&SD1, bleMcuStartBroadcast, 10);
    sdPut(&SD1, port);
}

void ble_connect(uint8_t port) {
    ledBleConnecting(port + 1);
    ble_connecting = true;

    if (port > 3) {
        port = 3;
    }
    sdWrite(&SD1, bleMcuConnect, 10);
    sdPut(&SD1, port);
    swtich_ble_driver();
}

void ble_disconnect(void) {
    /* Skip if the driver is already enabled */
    if (host_get_driver() != &ble_driver) {
        return;
    }

    clear_keyboard();
#ifdef NKRO_ENABLE
    keymap_config.nkro = lastNkroStatus;
#endif
    host_set_driver(lastHostDriver);
}

void ble_unpair(void) {
    sdPut(&SD1, 0x0);
    sdWrite(&SD1, bleMcuUnpair, 11);
}

void ble_read_data(void) {
    static ble_package_t ble_package = {._dummy = {0}, .caps_lock = false};

    // if there's stuff on the ble serial buffer
    // read it into the ble_package struct
    while(!sdGetWouldBlock(&SD1)) {
        sdReadTimeout(&SD1, (uint8_t *) &ble_package, sizeof(ble_package_t), 10);

        if (ble_package.caps_lock) {
            ble_led_state |= (1 << USB_LED_CAPS_LOCK); // set caps bit
        } else {
            ble_led_state &= ~(1 << USB_LED_CAPS_LOCK); // clear caps bit
        }

        if (ble_connecting) {
            ble_connecting = false;
            ledBleConnected();
        }

        if (ble_broadcasting) {
            // wait_ms(100);
            // ble_connect(ble_broadcasting-1);
            ble_broadcasting = 0;
        }
    }
}


/* ------------------- Static Function Implementation ----------------------- */
static void swtich_ble_driver(void) {
    if (host_get_driver() == &ble_driver) {
        return;
    }
    clear_keyboard();
    lastHostDriver = host_get_driver();
#ifdef NKRO_ENABLE
    lastNkroStatus = keymap_config.nkro;
#endif
    keymap_config.nkro = false;
    host_set_driver(&ble_driver);
}

static uint8_t ble_leds(void) {
    if(ble_connecting)
        return 0;
    else
        return ble_led_state;
}

static void ble_mouse(report_mouse_t *report){
}

static void ble_system(uint16_t data) {
}

static void ble_consumer(uint16_t data) {

}

/*!
 * @brief  Send keyboard HID report for Bluetooth driver
 */
static void ble_keyboard(report_keyboard_t *report) {
    sdPut(&SD1, 0x0);
    sdWrite(&SD1, bleMcuSendReport, 10);
    sdWrite(&SD1, &report->raw[0], 8);
}





