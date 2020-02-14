#ifndef SERIAL_PORT_H_
#define SERIAL_PORT_H_

#include "io430f5529.h"
#include "utility.h"
#include "circularBuffer.h"
#include "serialInfo.h"


#pragma region "BaudRate" 
/**
 * @brief 
 * In order to read:
 * UCBR  = (BAUD_xxxx >> 8);
 * UCBRS = (byte)(BAUD_xxxx);
 */
typedef enum BaudRate 
{
    //               UCBR        UCBRS
    BAUD_9600   = (104 << 8) | UCBRS_1, //<- These values may not work when sending out
    BAUD_19200  = (52  << 8) | UCBRS_0, //<- multiple bytes at a time
    BAUD_38400  = (26  << 8) | UCBRS_0, //<- 
    BAUD_57600  = (17  << 8) | UCBRS_3,
    BAUD_115200 = (8   << 8) | UCBRS_6
} BaudRate;
#pragma endregion

#pragma region "SerialPort"
typedef struct SerialPort
{ 
//\
Public:

    /**
     * @brief 
     * Info on this port.
     */
    SerialInfo info;

    /**
     * @brief 
     * The size of the rx and tx buffers,
     * in bytes.
     */
    uint buffSize;

    /**
     * @brief 
     * Initializes the  _serial port.
     * @param baudRate
     *      The baud rate used for the port,
     *      from the BaudRate::BAUD_xxxx enum.
     */
    void (*const begin)(BaudRate baudRate);

    /**
     * @brief 
     * Frees the underlying buffers.
     */
    void (*const close)(void);

    /**
     * @brief 
     * Reads a character from the rx buffer.
     * 
     * @param data The character read.
     * @return
     *      True if the character was read,
     *      false if the rx buffer was empty.
     */
    bool (*const readCharAsync)(byte *data);

    /**
     * @brief 
     * Blocks until a character is received on 
     * the rx buffer.
     * 
     * @return The character read.
     */
    byte (*const readChar)();

    /**
     * @brief 
     * Reads the given number of bytes
     * from the input buffer.
     * 
     * @param buffer The array that will contain the result.
     * @param bytes  The number of bytes to read (buffer size or less).
     */
    void (*const read)(byte *buffer, uint bytes);

    /**
     * @brief 
     * Reads the input buffer until it finds the 
     * given token.
     * 
     * @param buffer     The buffer that will hold the message.
     * @param size       The size of the given buffer.
     * @param terminator The token used as line terminator.
     * @return
     *      The number of bytes actually read.
     */
    uint (*const readUntil)(
        byte       *buffer, 
        uint        size, 
        const byte  terminator);

    /**
     * @brief 
     * Writes a character to the tx buffer.
     * 
     * @param data The character to write.
     * @return
     *      True if the tx buffer is not full,
     *      false otherwise.
     */
    bool (*const writeCharAsync)(const byte data);

    /**
     * @brief 
     * Writes a character to the tx buffer and waits
     * for it to be sent.
     */
    void (*const writeChar)(const byte data);

    /**
     * @brief
     * Writes a given message to the output buffer in a string
     * format (NULL terminated char array)
     * 
     * @param data The message to send.
     * @return
     *      The bytes actually written to the tx buffer.
     */
    uint (*const writeAsync)(const byte *data);

    /**
     * @brief
     * Writes a given message to the output buffer in a string
     * format (NULL terminated char array)
     * 
     * The function blocks until all the characters
     * have been sent.
     * 
     * @param data The message to send.
     */
    void (*const write)(const byte *data);

    /**
     * @brief
     * Writes a given message to the output buffer.
     * 
     * @param data 
     *      The bytes to write.
     *
     * @param length  
     *      The number of bytes to write (message length or less)
     *
     * @returns
     *      The number of bytes actually written.
     */
    uint (*const writeBuffAsync)(const byte *data, uint length);

    /**
     * @brief
     * Writes a given message to the output buffer.
     * Blocks until all the bytes have been sent.
     * 
     * @param data 
     *      The bytes to write.
     *
     * @param length  
     *      The number of bytes to write (message length or less)
     */
    void (*const writeBuff)(const byte *data, uint length);

//\
Private:

    CircularBuffer _tx;
    CircularBuffer _rx;

} SerialPort;
#pragma endregion


#endif // !SERIAL_PORT_H_