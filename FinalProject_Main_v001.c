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
#include "FinalProject_ButtonLibrary.h"
#include "FinalProject_MotionSensorLibrary.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)s
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void);

// various modes for operation
enum mode {
    startup = 0,
    ready = 1,
    armed = 2,
    tripped = 3,
    boom = 4,
};

struct Song {
    int tempo;
    int size;
    char notes[128][3];
};

/*
 * How to input a song:
 * 
 * Tempo: Enter the value in beats per minute as an integer
 * Size: Size indicates the number of notes in the melody
 * Notes: Each element consists of a 3-character input, a.k.a. length 3 string
 *        First character is a number that represents how many beats to hold a note. Because half
 *            beats are not permitted, it is recommended to set your tempo so one beat is the
 *            shortest note in the song. 
 *        Second character is the letter that indicates what letter note to play. Natural notes
 *            are represented by capital letters and flats are represented by lowercase letters.
 *        Third character is the number that indicates which octave the note should be played in
 */

 // Doof Theme
struct Song doof = {320, 11, 
{"1C3", "1A2", "2C3", "1E3", "1C3", "2E3", "2G3", "1G3", "3G3", "9G3", "1 3"}};
 
 // Perry Theme
struct Song perry = {172, 16, 
{"1D2", "1D2", "1E2", "1D2", "2F2", "1G2", "2D2", "1D2", "1E2", "1D2", "2F2", 
        "2G2", "2A3", "1a3", "3A3", "1 3"}};

enum mode curMode;
int setRange = 0; // range the sensor is calibrated to be at default
int curRange = 0; // current range being measured by the sensor

void setup(void)
{
    // execute once code goes here
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b1111111111111110;  //Set pin RA0 to output
    LATA = 0x0001;               //Set pin RA0 high
     
}

int main() {
       
    setup();    
    
    curMode = startup;
    writeColor(255,80,0);  
    
    initButtons(7,6);
    init_speaker(8);
    initMotionSensor(9);
    // lidar_init();
    
    curMode = ready;
    writeColor(0,0,255);
    
    while(1) {
        while(status == 0);
        status = 0;
       
        if (curMode == armed) {
            curMode = tripped;
            play_music(doof);
            writeColor(255,0,255);
       }
       
           
    }
    
    return 0;
}

// mode button
void __attribute__((__interrupt__,__auto_psv__)) _INT1Interrupt(void) {
   _INT1IF = 0;
   
   // if trap is ready to be armed, it is now armed
   if (curMode == ready) {
       curMode = armed;
       writeColor(255,0,0);
   } 
   
   // if the trap is armed, it is now disarmed
   else if (curMode == armed) {
       curMode = ready;
       writeColor(0,0,255);
   }
   
   // if trap was already tripped, it is armed again
   else if (curMode == tripped) {
       curMode = armed;
       writeColor(255,0,0);
   }
   
}

// self destruct button
void __attribute__((__interrupt__,__auto_psv__)) _INT2Interrupt(void) {
    _INT2IF = 0;
    

    
    if (curMode != boom) {
    
        writeColor(255,255,0);
        
        curMode = boom;
        
    // plays the perry theme
    play_music(perry);

        // potential animation light ??
    }
}