#include "xc.h"

void initMotionSensor(){
    
    TRISBbits.TRISB9 = 1; // enable pin input on RP9
    
     __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
     
    RPINR7bits.IC1R = 9; 
     
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
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

