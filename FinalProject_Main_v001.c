/*
 * File:   FinalProject_Main_v001.c
 * Author: gahym
 *
 * Created on April 12, 2023, 11:19 AM
 */
#include "xc.h"
#include "FinalProject_LEDLibrary.h"
#include "FinalProject_LIDARLibrary.h"
#include "FinalProject_MusicLibrary.h"

void setup(void);
int main(void);
void initButtons(void);

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

enum mode {
    startup = 0,
    ready = 1,
    armed = 2,
    tripped = 3,    
};

enum mode curMode;

void setup(void)
{
    // execute once code goes here
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b1111111111111110;  //Set pin RA0 to output
    LATA = 0x0001;               //Set pin RA0 high
    
    curMode = startup;
    writeColor(255,80,0);
}

int main(void) {
    setup();    
    initButtons();   
    
    curMode = ready;
    
    while(1){
                    
    }
    
    return 0;
}

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
}

// mode button
void __attribute__((__interrupt__,__auto_psv__)) _INT1Interrupt(void) {
   _INT1IF = 0;
   
   // change mode
   if (curMode == ready) {
       curMode = armed;
       writeColor(255,0,0);
       // do else 
   } 
}

// self destruct button
void __attribute__((__interrupt__,__auto_psv__)) _INT2Interrupt(void) {
    _INT2IF = 0;
    
    
    // do whatever after self destruct
    writeColor(255,255,0);
    
    
}