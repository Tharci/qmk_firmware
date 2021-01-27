#pragma once

#include "annepro2.h"
#include "quantum.h"

void ble_startup(void);
void ble_broadcast(uint8_t port);
void ble_connect(uint8_t port);
void ble_disconnect(void);
void ble_unpair(void);
void ble_read_data(void);


typedef struct __attribute__((__packed__)) {
    uint8_t _dummy[10];
    bool caps_lock;
} ble_package_t;

