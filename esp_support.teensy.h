#ifndef ESPSUPPORT_H
#define ESPSUPPORT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TEENSY_HWSERIAL_BAUD 115200

#define ESP_SERIAL_INIT(data)                     TeensyEspInit(data)
#define ESP_SERIAL_CLEANUP(data)                  TeensyEspCleanup(data)
#define ESP_SERIAL_AVAILABLE(data)                TeensyEspAvailable(data)
#define ESP_SERIAL_WAIT_AVAILABLE(data,msec)      TeensyEspWaitAvailable(data,msec)
#define ESP_SERIAL_READ_BYTE(data,byte)           TeensyEspReadByte(data,byte)
#define ESP_SERIAL_READ_BUFF(data,buffer,length)  TeensyEspReadBuff(data,buffer,length)
#define ESP_SERIAL_WRITE_BYTE(data,byte)          TeensyEspWriteByte(data,byte)
#define ESP_SERIAL_WRITE_BUFF(data,buffer,length) TeensyEspWriteBuff(data,buffer,length)

bool TeensyEspInit(void *data);
bool TeensyEspCleanup(void *data);
bool TeensyEspAvailable(void *data);
bool TeensyEspWaitAvailable(void *data, uint16_t msec);
bool TeensyEspReadByte(void *data, uint8_t *byte);
bool TeensyEspReadBuff(void *data, uint8_t *buffer, uint16_t length);
void TeensyEspWriteByte(void *data, uint8_t byte);
void TeensyEspWriteBuff(void *data, uint8_t *buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif // ESPSUPPORT_H

