#ifndef ESPSUPPORT_H
#define ESPSUPPORT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_SERIAL_INIT(data)                     QtEspInit(data)
#define ESP_SERIAL_CLEANUP(data)                  QtEspCleanup(data)
#define ESP_SERIAL_AVAILABLE(data)                QtEspAvailable(data)
#define ESP_SERIAL_WAIT_AVAILABLE(data,msec)      QtEspWaitAvailable(data,msec)
#define ESP_SERIAL_READ_BYTE(data,byte)           QtEspReadByte(data,byte)
#define ESP_SERIAL_READ_BUFF(data,buffer,length)  QtEspReadBuff(data,buffer,length)
#define ESP_SERIAL_WRITE_BYTE(data,byte)          QtEspWriteByte(data,byte)
#define ESP_SERIAL_WRITE_BUFF(data,buffer,length) QtEspWriteBuff(data,buffer,length)

bool QtEspInit(void *data);
bool QtEspCleanup(void *data);
bool QtEspAvailable(void *data);
bool QtEspWaitAvailable(void *data, uint16_t msec);
bool QtEspReadByte(void *data, uint8_t *byte);
bool QtEspReadBuff(void *data, uint8_t *buffer, uint16_t length);
void QtEspWriteByte(void *data, uint8_t byte);
void QtEspWriteBuff(void *data, uint8_t *buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif // ESPSUPPORT_H
