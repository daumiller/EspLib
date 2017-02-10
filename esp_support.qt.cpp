#include "esp_support.qt.h"
#include <QSerialPort>
#include <stdio.h>

bool QtEspInit(void *data) {
    QSerialPort *qsp = (QSerialPort *)data;
    if(!qsp->open(QIODevice::ReadWrite)) { return false; }
    return true;
}

bool QtEspCleanup(void *data) {
    QSerialPort *qsp = (QSerialPort *)data;
    qsp->close();
    delete qsp;
    return true;
}

bool QtEspAvailable(void *data) {
    QSerialPort *qsp = (QSerialPort *)data;
    return (qsp->bytesAvailable() > 0);
}

bool QtEspWaitAvailable(void *data, uint16_t msec) {
    QSerialPort *qsp = (QSerialPort *)data;
    if(msec) {
        if(qsp->bytesAvailable())       { return true; }
        if(qsp->waitForReadyRead(msec)) { return true; }
        return false;
    }

    while(true) {
        if(qsp->bytesAvailable())      { return true; }
        if(qsp->waitForReadyRead(500)) { return true; }
    }
}

bool QtEspReadByte(void *data, uint8_t *byte) {
    QSerialPort *qsp = (QSerialPort *)data;
    QtEspWaitAvailable(data, 0);
    char charbuff;
    qint64 result = qsp->read(&charbuff, 1);
    while(result < 1) {
        if(result == -1) { return false; }
        result = qsp->read((char *)&charbuff, 1);
    }
    *byte = charbuff;
    printf("%c", charbuff);
    return true;
}

bool QtEspReadBuff(void *data, uint8_t *buffer, uint16_t length) {
    QSerialPort *qsp = (QSerialPort *)data;
    uint16_t read_total = 0; int read_current;
    while(read_total < length) {
        QtEspWaitAvailable(data, 0);
        read_current = qsp->read((char *)(buffer+read_total), (qint64)(length-read_total));
        if(read_current == -1) { return false; }
        read_total += read_current;
    }
    return true;
}

void QtEspWriteByte(void *data, uint8_t byte) {
    printf("%c", byte);
    QSerialPort *qsp = (QSerialPort *)data;
    qsp->write((const char *)&byte, 1);
}

void QtEspWriteBuff(void *data, uint8_t *buffer, uint16_t length) {
    for(uint16_t ii=0; ii<length; ++ii) { printf("%c", buffer[ii]); }
    QSerialPort *qsp = (QSerialPort *)data;
    qsp->write((const char *)buffer, (qint64)length);
}
