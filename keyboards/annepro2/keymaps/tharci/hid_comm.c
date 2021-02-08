#include "hid_comm.h"

#include "led.h"
#include "persistence.h"

typedef enum {
    Weather = 0, Gaming, Notification
} MessageType;

void hid_handle(uint8_t* data, uint8_t length) {
    if (data[0] == Weather && length > 1) {
        ledSetWeather(data + 1, length - 1);
    }
}


