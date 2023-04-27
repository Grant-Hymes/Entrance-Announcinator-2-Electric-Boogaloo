#include "xc.h"

/**
 * The function Initailzies external interrupt 1 and 2 to the two given pins
 * Two buttons are assumed to be wired into different pins from 6 to 9
 * The other end of the button must be wired into ground
 * pull up resistors are enabled. When the button is pressed, the attached pin will be forced to ground
 * The external interrupt is set to negative edge mode, detecting this change and running the interrupt.
 * @param pin1 pin to be associated with external interrupt 1 (mode button)
 * @param pin2 pin to be associated with external interrupt 2 (self destruct button)
 */

void initButtons(int pin1, int pin2) {
    
    // ensures both pins are within 6 to 9
    if ( (pin1 < 6) || (pin1 > 9) || (pin2 < 6) || (pin2 > 9) ) {
        return;
    }
    
    // if the given pins are the same, return
    if (pin1 == pin2) {
        return;
    }
    
    // sets pull up resistors and pin input
    if ( (pin1 == 6) || (pin2 == 6) ) {
        TRISBbits.TRISB6 = 1;
        CNPU2bits.CN24PUE = 1; // set RP6 pull up resistor
    } if ( (pin1 == 7) || (pin2 == 7) ) {
        TRISBbits.TRISB7 = 1;
        CNPU2bits.CN23PUE = 1; // set RP7 pull up resistor
    } if ( (pin1 == 8) || (pin2 == 8) ) {
        TRISBbits.TRISB8 = 1;
        CNPU2bits.CN22PUE = 1; // set RP8 pull up resistor
    } if ( (pin1 == 9) || (pin2 == 9) ) {
        TRISBbits.TRISB9 = 1;
        CNPU2bits.CN21PUE = 1; // set RP9 pull up resistor
    }
        
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
     
    RPINR0bits.INT1R = pin1;  // Use given Pin1 for External Interrupt 1
    RPINR1bits.INT2R = pin2;  // Use given Pin2 for External Interrupt 2 
     
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    _INT1EP = 1; // negative edge
    _INT2EP = 1; 
    _INT1IF = 0; // reset interrupt flag
    _INT2IF = 0;
    _INT1IE = 1; // interrupt enable
    _INT2IE = 1;
    _INT2IP = 7; // self destruct has interrupt priority
}
