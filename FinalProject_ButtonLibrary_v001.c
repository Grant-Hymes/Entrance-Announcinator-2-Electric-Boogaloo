#include "xc.h"

void initButtons(void) {
    TRISBbits.TRISB7 = 1; // enable pin input on RB7
    TRISBbits.TRISB6 = 1; // enable pin input on RP6
    CNPU2bits.CN23PUE = 1; // set RP7 pull up resistor
    CNPU2bits.CN24PUE = 1; // set RP6 pull up resistor
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
     
    RPINR0bits.INT1R = 7;  // Use Pin RP7 for External Interrupt 1
    RPINR1bits.INT2R = 6;  // Use Pin RP6 for External Interrupt 2 
     
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    _INT1EP = 1; // negative edge
    _INT2EP = 1; // negative edge
    _INT1IF = 0; // reset interrupt flag
    _INT2IF = 0;
    _INT1IE = 1; // interrupt enable
    _INT2IE = 1;
    _INT2IP = 7; // self destruct has interrupt priority
}
