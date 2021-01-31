#include "hid_comm.h"

#include "led.h"
#include "persistence.h"


void hid_handle(uint8_t *data, uint8_t length) {
    pers_toggleLock();
}


