#ifndef SERIAL_INFO_H_
#define SERIAL_INFO_H_

#include "utility.h"


typedef struct SerialInfo
{
    volatile 
    byte *pxSel;
    byte  pxSelVal;
    
    volatile byte *UCAIFG;
    volatile byte *UCAIE;

    volatile byte *UCACTL1;
    volatile byte *UCAMCTL;

    volatile byte *UCABR0;
    volatile byte *UCABR1;

    const 
    volatile byte *UCARXBUF;
    volatile byte *UCATXBUF;
} SerialInfo;


#endif // !SERIAL_INFO_H_