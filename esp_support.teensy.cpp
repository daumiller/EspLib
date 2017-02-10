#include "esp_support.teensy.h"
#include "WProgram.h"

// make sure to set your SERIAL1_RX_BUFFER_SIZE, or equivalent parameter to a >64 value (256 seems to work well).

bool TeensyEspInit(void *data) {
    HardwareSerial *ser = (HardwareSerial *)data;
    ser->begin(TEENSY_HWSERIAL_BAUD);
    return true;
}

bool TeensyEspCleanup(void *data) {
    HardwareSerial *ser = (HardwareSerial *)data;
    ser->end();
    return true;
}

bool TeensyEspAvailable(void *data) {
    HardwareSerial *ser = (HardwareSerial *)data;
    return (ser->available() > 0);
}

bool TeensyEspWaitAvailable(void *data, uint16_t msec) {
    HardwareSerial *ser = (HardwareSerial *)data;
    if(msec) {
      if(ser->available()) { return true; }
      delay(msec);
      if(ser->available()) { return true; }
      return false;
    }

    while(true) {
        if(ser->available()) { return true; }
        delay(250);
        if(ser->available()) { return true; }
    }
}

bool TeensyEspReadByte(void *data, uint8_t *byte) {
    HardwareSerial *ser = (HardwareSerial *)data;
    TeensyEspWaitAvailable(data, 0);
    int result = ser->read();
    if(result == -1) { return false; }
    *byte = (uint8_t)result;
    return true;
}

bool TeensyEspReadBuff(void *data, uint8_t *buffer, uint16_t length) {
    HardwareSerial *ser = (HardwareSerial *)data;
    uint16_t read_total = 0; int result;
    while(read_total < length) {
        TeensyEspWaitAvailable(data, 0);
        result = ser->read();
        if(result == -1) { return false; }
        *buffer = (uint8_t)result;
        ++read_total;
        ++buffer;
    }
    return true;
}

void TeensyEspWriteByte(void *data, uint8_t byte) {
    HardwareSerial *ser = (HardwareSerial *)data;
    ser->write(byte);
}

void TeensyEspWriteBuff(void *data, uint8_t *buffer, uint16_t length) {
    HardwareSerial *ser = (HardwareSerial *)data;
    ser->write(buffer, length);
}

