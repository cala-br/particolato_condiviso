#ifndef UTILITY_H
#define UTILITY_H


#ifndef NULL
#define NULL 0
#endif // !NULL


#ifndef HIGH
#define HIGH 0x1
#endif // !HIGH


#ifndef LOW
#define LOW 0x0
#endif // !LOW


#ifndef BYTE_HIGH
#define BYTE_HIGH 0xFF
#endif // !BYTE_HIGH


typedef unsigned char byte;
typedef unsigned int  uint;
typedef unsigned long ulong;


/**
 * @brief Reads the state of a port from a register.
 * Returns HIGH if the port is 1, LOW otherwise.
 * 
 * @param reg:   The port's register
 * @param port:  The port's bit (BITx)
 */
#define READ_PORT(reg, bit)    \
    (((reg) & (bit)) ? HIGH : LOW)

      
/**
 * @brief Sets a port HIGH or LOW.
 * 
 * @param reg:   The port's register
 * @param port:  The port's bit (BITx)
 * @param value: The value to set, either HIGH or LOW
 */    
#define SET_PORT(reg, bit, value)    \
    ((value) ? (reg) |= (bit) : (reg) &= ~(bit))


/** 
 * @brief Switches the state of a port.
 * 
 * @param reg:   The port's register
 * @param port:  The port's bit (BITx)
 */      
#define SWITCH_PORT(reg, bit)    \
    ((reg) ^= (bit))
      
/*
 * @brief Raises an event if the pointer to the
 * function is not NULL.
 */
#define RAISE_EVENT(functionPointer)       \
    do { if ((functionPointer) != NULL)    \
        (functionPointer)(); } while(0)


/**
 * @brief Represents a boolean value.
 */
typedef enum bool {false, true} bool;


/**
 * @brief Represents the states that
 * a switch can take.
 */
typedef enum State
{
    PRESSED      = 0x00,
    JUST_PRESSED ,
    JUST_RELEASED,
    RELEASED     = 0xFF
} State;


inline void clamp(ulong *value, ulong min, ulong max)
{
    if (*value < min) 
        *value = min;

    else if (*value > max) 
        *value = max;
}


#endif // !UTILITY_H