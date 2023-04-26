#include "xc.h"


/**
 * The function initializes a PIR motion sensor, assuming one is attached to a chosen pin
 * The function sets up output compare 1, using timer 2, and assigns it to the pin
 * Output Compare 1 is used to determine when the pin recieves a high voltage
 * optional pins include RP6, RP7, RP8, RP9
 * @param pin the pin the motion sensor/ output compare will be mapped to
 */

void initMotionSensor(int pin){
      
    if (pin > 9 || pin < 6) {
        return;
    }
    
    if (pin == 6) {
        TRISBbits.TRISB6 = 1;
    } else if (pin == 7) {
        TRISBbits.TRISB7 = 1;
    } else if (pin == 8) {
        TRISBbits.TRISB8 = 1;
    } else if (pin == 9) {
        TRISBbits.TRISB9 = 1;
    }
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
     
    RPINR7bits.IC1R = pin; // set input capture 6 to pin 9
     
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    // the remainder of the function sets up the appropriate registers for
    // input capture 1 and timer 2
    
    IC1CON = 0;
    IC1CONbits.ICM = 011; // set input capture mode
                         // every rising edge
    
    IC1CONbits.ICTMR = 1; // use timer 2
    
    // timer 2 configuration
    T2CON = 0;
    T2CONbits.TCKPS = 0b11;
    PR2 = 62499;
    TMR2 = 0;
    
    _T2IE = 0; // timer 2 interrupt enable
    _T2IF = 0; // timer 2 interrupt flag
   
    _IC1IE = 1; // enable input capture interrupt
    _IC1IF = 0; // reset input capture 1 interrupt flag
    
    T2CONbits.TON = 1;
    
    }

