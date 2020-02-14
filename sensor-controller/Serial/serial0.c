#include "serial0.h"


CREATE_SERIAL_PORT_CALLBACKS(serial0, Serial)

SerialPort Serial =
{
    .info = 
    {
        .pxSel    = &P4SEL,
        .pxSelVal = BIT4 + BIT5,

        .UCAIFG = &UCA1IFG,
        .UCAIE  = &UCA1IE,

        .UCACTL1 = &UCA1CTL1,
        .UCAMCTL = &UCA1MCTL,

        .UCABR0 = &UCA1BR0,
        .UCABR1 = &UCA1BR1,

        .UCARXBUF = &UCA1RXBUF,
        .UCATXBUF = &UCA1TXBUF
    },
    .buffSize = 16,
    SERIAL_GET_CALLBACK_REFERENCES(serial0)
};


#pragma vector = USCI_A1_VECTOR
__interrupt void __serial0_interrupt(void)
{
    _serialInterruptBase(&Serial);
}

