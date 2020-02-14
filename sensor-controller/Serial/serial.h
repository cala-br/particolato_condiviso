#ifndef SERIAL_H_
#define SERIAL_H_

#include "serialPort.h"


#pragma region "Serial macros"

#define SERIAL_DATA_RECEIVED(pSerialInfo) (*(pSerialInfo).UCAIFG & UCRXIFG)
#define SERIAL_ENABLE_RX(pSerialInfo)     (*(pSerialInfo).UCAIE |=  UCRXIE)
#define SERIAL_DISABLE_RX(pSerialInfo)    (*(pSerialInfo).UCAIE &= ~UCRXIE)

#define SERIAL_TX_AVAILABLE(pSerialInfo)  (*(pSerialInfo).UCAIFG & UCTXIFG)
#define SERIAL_TX_ENABLED(pSerialInfo)    (*(pSerialInfo).UCAIE  &  UCTXIE)
#define SERIAL_ENABLE_TX(pSerialInfo)     (*(pSerialInfo).UCAIE |=  UCTXIE) 
#define SERIAL_DISABLE_TX(pSerialInfo)    (*(pSerialInfo).UCAIE &= ~UCTXIE)

#define SERIAL_ENABLE_RESET(pSerialInfo)  (*(pSerialInfo).UCACTL1 |=  UCSWRST)
#define SERIAL_DISABLE_RESET(pSerialInfo) (*(pSerialInfo).UCACTL1 &= ~UCSWRST)

#define SERIAL_READ(pSerialInfo)        (*(pSerialInfo).UCARXBUF)
#define SERIAL_WRITE(pSerialInfo, data) (*(pSerialInfo).UCATXBUF = data)

/**
 * @brief 
 * Executes the given code while
 * the transmission is locked.
 */
#define SERIAL_LOCK_TX(pSerialInfo, expr)   \
    do {                                    \
        SERIAL_DISABLE_TX(pSerialInfo);     \
        expr                                \
        SERIAL_ENABLE_TX(pSerialInfo);      \
    } while (0)       


/**
 * @brief 
 * Execute the given code while
 * the USCI interface is in reset
 * mode.
 */
#define SERIAL_RESET(pSerialInfo, expr)     \
    do {                                    \
        SERIAL_ENABLE_RESET(pSerialInfo);   \
        expr                                \
        SERIAL_DISABLE_RESET(pSerialInfo);  \
    } while (0)

#pragma endregion


#pragma region "Function prototypes"


void computeUCBR(
    float freq, 
    float baudRate, 
    byte *ucbr0, 
    byte *ucbr1, 
    byte *ucbrs,
    bool  useUCOS16Oversampling);


void  _serialBegin(SerialPort *serial, BaudRate baudRate);
void  _serialClose(SerialPort *serial);


bool  _serialReadCharAsync(SerialPort *serial, byte *data);
byte  _serialReadChar     (SerialPort *serial);
void  _serialRead         (SerialPort *serial, byte *buffer, uint bytes);


bool  _serialWriteCharAsync(SerialPort *serial, const byte data);
void  _serialWriteChar     (SerialPort *serial, const byte data);
void  _serialWrite         (SerialPort *serial, const byte *data);


uint  _serialWriteAsync    (SerialPort *serial, const byte *data);
void  _serialWriteBuff     (SerialPort *serial, const byte *data, uint length);
uint  _serialWriteBuffAsync(SerialPort *serial, const byte *data, uint length);


uint  _serialReadUntil(
    SerialPort *serial,
    byte       *buffer, 
    uint        size, 
    const byte  terminator);


void _serialInterruptBase(SerialPort *serial);

#pragma endregion


#pragma region "Create serial port callbacks"
#define CREATE_SERIAL_PORT_CALLBACKS(portName, serialObj)\
    static inline void __ ## portName ## _begin(BaudRate baudRate)\
    {\
        _serialBegin(&(serialObj), baudRate);\
    }\
\
    static inline void __ ## portName ## _close()\
    {\
        _serialClose(&(serialObj));\
    }\
\
    static inline bool __ ## portName ## _readCharAsync(byte *data)\
    {\
        return _serialReadCharAsync(&(serialObj), data);\
    }\
\
    static inline byte __ ## portName ## _readChar()\
    {\
        return _serialReadChar(&(serialObj));\
    }\
\
    static inline void __ ## portName ## _read(byte *buffer, uint bytes)\
    {\
        _serialRead(&(serialObj), buffer, bytes);\
    }\
\
    static inline uint __ ## portName ## _readUntil(byte *buffer, uint size, const byte terminator)\
    {\
        return _serialReadUntil(&(serialObj), buffer, size, terminator);\
    }\
\
    static inline bool __ ## portName ## _writeCharAsync(const byte data)\
    {\
        return _serialWriteCharAsync(&(serialObj), data);\
    }\
\
    static inline void __ ## portName ## _writeChar(const byte data)\
    {\
        _serialWriteChar(&(serialObj), data);\
    }\
\
    static inline uint __ ## portName ## _writeAsync(const byte *data)\
    {\
        return _serialWriteAsync(&(serialObj), data);\
    }\
\
    static inline void __ ## portName ## _write(const byte *data)\
    {\
        _serialWrite(&(serialObj), data);\
    }\
\
    static inline uint __ ## portName ## _writeBuffAsync(const byte *data, uint length)\
    {\
        return _serialWriteBuffAsync(&(serialObj), data, length);\
    }\
\
    static inline void __ ## portName ## _writeBuff(const byte *data, uint length)\
    {\
        _serialWriteBuff(&(serialObj), data, length);\
    }
#pragma endregion
    
#pragma region "Serial get callback references"
#define SERIAL_GET_CALLBACK_REFERENCES(portName)\
    .begin = &__ ## portName ## _begin,\
    .close = &__ ## portName ## _close,\
\
    .readCharAsync = &__ ## portName ## _readCharAsync,\
    .readChar      = &__ ## portName ## _readChar,\
    .read          = &__ ## portName ## _read,\
\
    .readUntil = &__ ## portName ## _readUntil,\
\
    .writeCharAsync = &__ ## portName ## _writeCharAsync,\
    .writeChar      = &__ ## portName ## _writeChar,\
\
    .writeAsync = &__ ## portName ## _writeAsync,\
    .write      = &__ ## portName ## _write,\
\
    .writeBuffAsync = &__ ## portName ## _writeBuffAsync,\
    .writeBuff      = &__ ## portName ## _writeBuff
#pragma endregion


#endif // !SERIAL_H_