#include "xc.h"
#include "FinalProject_ASMLibrary.h"
/**
 * Assuming there is an WS2812 or architecturally similar LED on pin RA0
 * this function changes it's color based on the given R, G and B values
 * higher values result in higher brightness for that specific color.
 * (255,255,255) produces a white light, (0,0,0) produces no light
 * @param r red value to be sent to the LED, can be from 0 to 255.
 * @param g green value to be sent to the LED, can be from 0 to 255.
 * @param b blue value to be sent to the LED, can be from 0 to 255.
 */
 void writeColor(int r, int g, int b){ 
    
    // writes red color
    for (int i = 128; i > 0; i = i>>1) {
        if (r&i) {
            write_1();
        } else {
            write_0();
        }
    }
    
    // writes green color
    for (int i = 128; i > 0; i = i>>1) {
        if (g&i) {
            write_1();
        } else {
            write_0();
        }
    }
    
    // writes blue color
    for (int i = 128; i > 0; i = i>>1) {
        if (b&i) {
            write_1();
        } else {
            write_0();
        }
    }
        
    // allows for reset to work     
    delay_100us();
        
}