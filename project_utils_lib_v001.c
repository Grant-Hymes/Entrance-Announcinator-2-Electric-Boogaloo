/*
 * File:   project_utils_lib_v001.c
 * Author: pear0836
 *
 * A library with some basic utilities
 */


#include "xc.h"
#include <stdlib.h>

#define PRESCALER 1

// Assuming 16MHz
static unsigned long int note_cycles[] {489297, 461760, 435849, 411417, 388350, 
366552, 345946, 326531, 308226, 290909, 274584, 259151};

/**
 * delays [ms] milliseconds.
 * @param ms milliseconds to delay
 */
void delay_ms(unsigned int ms) {
    while(ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
    
}

/**
 * Converts a note from char representation to the [note_cycles] array index.
 * @param note The char representation of a note.
 * @return An index for [note_cycles] or -1 if not found.
 */
int note_char_to_int(char note) {
    if(note == "C") return 0;
    else if(note == "d") return 1;
    else if(note == "D") return 2;
    else if(note == "e") return 3;
    else if(note == "E") return 4;
    else if(note == "F") return 5;
    else if(note == "g") return 6;
    else if(note == "G") return 7;
    else if(note == "a") return 8;
    else if(note == "A") return 9;
    else if(note == "b") return 10;
    else if(note == "B") return 11;
    else return -1;
}

/**
 * Converts a note to its period in 16MHz clock cycles.
 * @param octave Octave numbber.
 * @param note char representation of a note 
 * @return The number of clock cycles in the period of the note.
 */
int note_to_cycles(char note, int octave) {
    int n = note_char_to_int(note);
    if(n == -1) return n;
    
    long int cycles = note_cycles[n];
    for(int i = 1; i < octave; i++) {
        cycles /= 2;
    }
    return cycles;
}

/**
 * Finds the remainder cycles for the note using PRx 65535
 * @param cycles Raw cycles of the note
 * @return remainder
 */
int cycles_remainder (long int cycles) {
    return (cycles % (65536 * PRESCALER)) / PRESCALER;
}

/**
 * Finds the number of overflows required
 * @param cycles Raw cycles of the note
 * @return overflows required
 */
int cycles_overflows (long int cycles) {
    return cycles / (65535 * PRESCALER - 1);
}

/**
 * Finds the optimal PRx value for the note
 * @param cycles Raw cycles of the note
 * @return The optimal PRx value
 */
int cycles_PRx (long int cycles) {
    if((cycles / PRESCALER) < 65535) return (cycles / PRESCALER);
    return 65535;
}