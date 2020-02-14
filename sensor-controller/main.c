#include "io430f5529.h"
#include "serial0.h"


int main(void)
{   
    WDTCTL = WDTPW + WDTHOLD;
    
    __enable_interrupt();
    Serial.begin(BAUD_115200);
    
    byte *msg = "hello world"; //[12]
    while (true)
    {
        switch (Serial.readChar())
        {
            case 'a':
                Serial.writeCharAsync('a'); 
                break;
            
            // Enter pressed
            case '\r':
                Serial.writeCharAsync(*msg++);

                if (*msg == '\0') msg -= 11;
                break;

            case 'e': goto end; 
        }
    }

    end: while (true)
        ;
}