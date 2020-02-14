#include "serial.h"
#include <math.h>


#pragma region "Compute UCBR"
/**
 * @brief 
 * Computes the UCBRSx and UCBRx values
 * for the given frequency and baudRate
 * 
 * Useful links for baud rate calculation:
 * - https://forum.43oh.com/topic/2640-uart-configurator/
 * - http://processors.wiki.ti.com/index.php?title=USCI_UART_Baud_Rate_Gen_Mode_Selection&oldid=122242
 * - http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 * - http://e2e.ti.com/support/microcontrollers/msp430/f/166/t/51342?UART-setup-with-UCOS16-1-generates-framing-errors-on-MSP430F2618
 */
void computeUCBR(
    float  freq, 
    float  baudRate, 
    byte  *ucbr0, 
    byte  *ucbr1, 
    byte  *ucbrs,
    bool   useUCOS16Oversampling
)
{
    byte div = 
        useUCOS16Oversampling ? 16 : 1;
        
    float val = 
        freq / baudRate / div;

    *ucbr0 = (byte)val % 256; 
    *ucbr1 = (byte)val / 256; 
    *ucbrs = (byte)round((val - (uint)val) * 8);
}
#pragma endregion


#pragma region "Serial begin"
/**
 * @brief 
 *      Initializes the  _serial port.
 * @param baudRate
 *      The baud rate used for the port,
 *      from the BaudRate::BAUD_xxxx enum.
 */
void _serialBegin(SerialPort *serial, BaudRate baudRate)
{
    *(serial->info.pxSel) |= serial->info.pxSelVal;

    SERIAL_RESET(serial->info,
    {
        // 1MHz clock
        *(serial->info.UCACTL1) |= UCSSEL_2;
        *(serial->info.UCAMCTL) |= UCBRF_0;  
        
        // Baud rate
        *(serial->info.UCABR0)   = baudRate >> 8;
        *(serial->info.UCABR1)   = 0;
        *(serial->info.UCAMCTL) |= (byte)baudRate;
    });
    
    SERIAL_ENABLE_RX(serial->info);

    cbInit(&serial->_tx, serial->buffSize);
    cbInit(&serial->_rx, serial->buffSize);
}
#pragma endregion

#pragma region "Serial close"
/**
 * @brief 
 * Frees the underlying buffers.
 */
inline void _serialClose(SerialPort *serial)
{
    cbFree(&serial->_tx);
    cbFree(&serial->_rx);
}
#pragma endregion


#pragma region "Serial read char async"
/**
 * @brief 
 * Reads a character from the rx buffer
 * asynchronously.
 * 
 * @param data The character read.
 * @return
 *      True if the character was read,
 *      false if the rx buffer was empty.
 */
inline bool _serialReadCharAsync(SerialPort *serial, byte *data)
{
    return cbRead(&serial->_rx, data);
}
#pragma endregion

#pragma region "Serial read char"
/**
 * @brief 
 * Blocks until a character is received on 
 * the rx buffer.
 * 
 * @return The character read.
 */
inline byte _serialReadChar(SerialPort *serial)
{
    byte res;
    while (!_serialReadCharAsync(serial, &res))
        ;
    
    return res;
}
#pragma endregion

#pragma region "Serial read"
/**
 * @brief 
 * Reads the given number of bytes
 * from the input buffer.
 * 
 * @param buffer The array that will contain the result.
 * @param bytes  The number of bytes to read (buffer size or less).
 */
inline void _serialRead(
    SerialPort *serial, 
    byte       *buffer, 
    uint        bytes
)
{
    for (; bytes > 0; --bytes)
        *(buffer++) = _serialReadChar(serial);
}
#pragma endregion


#pragma region "Serial write char async"
/**
 * @brief 
 * Writes a character to the tx buffer
 * asynchronously.
 * 
 * @param data The character to write.
 * @return
 *      True if the tx buffer is not full,
 *      false otherwise.
 */
bool _serialWriteCharAsync(
    SerialPort *serial, 
    const byte  data
)
{
    bool ret;
    SERIAL_LOCK_TX(serial->info,
    {
        ret = 
            cbWrite(&serial->_tx, data);
    });
    return ret;
}
#pragma endregion

#pragma region "Serial write char"
/**
 * @brief 
 * Writes a character to the tx buffer and waits
 * for it to be sent.
 */
void _serialWriteChar(
    SerialPort *serial, 
    const byte  data
)
{
    while (!_serialWriteCharAsync(serial, data))
        ;

    // Waiting for byte to be sent.
    while(!SERIAL_TX_AVAILABLE(serial->info))
        ;
}
#pragma endregion

#pragma region "Serial write"
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
inline void _serialWrite(
    SerialPort *serial, 
    const byte *data
)
{
    while(*data)
        _serialWriteChar(serial, *data++);
}
#pragma endregion


#pragma region "Serial write async"
/**
 * @brief
 * Writes a given message to the output buffer in a string
 * format (NULL terminated char array)
 * 
 * @param data The message to send.
 * @return
 *      The bytes actually written to the tx buffer.
 */
uint _serialWriteAsync(
    SerialPort *serial, 
    const byte *data
)
{
    int i;
    SERIAL_LOCK_TX(serial->info,
    {
        for(i = 0; data[i]; ++i)
            if(!cbWrite(&serial->_tx, data[i]))
                break;
    });
    return i;
}
#pragma endregion

#pragma region "Serial write buff"
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
inline void _serialWriteBuff(
    SerialPort *serial, 
    const byte *data, 
    uint        length
)
{
    while(--length > 0)
        _serialWriteChar(serial, *data++);
}
#pragma endregion

#pragma region "Serial write buff async"
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
uint _serialWriteBuffAsync(
    SerialPort *serial, 
    const byte *data, 
    uint        length
)
{
    int i;
    SERIAL_LOCK_TX(serial->info,
    {
        for(i = 0; i < length; ++i)
            if(!cbWrite(&serial->_tx, data[i]))
                break;
    });
    return i;
}
#pragma endregion


#pragma region "Serial read until"
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
uint _serialReadUntil(
    SerialPort *serial,
    byte       *buffer, 
    uint        size, 
    const byte  terminator
) 
{
    int i;
    for (i = 0; i < size; i++)
    {
        buffer[i] = _serialReadChar(serial);
        if (buffer[i] == terminator)
            break;
    }

    return i + 1;
}
#pragma endregion


#pragma region "Serial interrupt base"
void _serialInterruptBase(SerialPort *serial)
{
    static byte data;
    
    // Reading
    if(SERIAL_DATA_RECEIVED(serial->info))
    {
        cbWrite(
            &serial->_rx, 
            SERIAL_READ(serial->info));
    }

    // Writing
    if(SERIAL_TX_AVAILABLE(serial->info) && SERIAL_TX_ENABLED(serial->info))
    {	
    	if(cbIsEmpty(&serial->_tx)) 
        {
            SERIAL_DISABLE_TX(serial->info);
            return;
        }

        // Data to send
    	cbRead(&serial->_tx, &data);
        SERIAL_WRITE(serial->info, data);
    }
}
#pragma endregion
