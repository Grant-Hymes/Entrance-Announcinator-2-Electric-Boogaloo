/*
 * File:   FinalProject_MusicLibrary_v002.c
 * Author: pear0836
 *
 * A library to handle playing notes and music correctly
 */


#include "xc.h"
#include <stdlib.h>

// cycles = 1 / freq / Tcy

// Octave 1 cycles, assuming Fcy = 16MHz
static unsigned long int note_cycles[] {489297, 461760, 435849, 411417, 388350, 
366552, 345946, 326531, 308226, 290909, 274584, 259151};

//Example
int hold[] = {0, 1};
char note[] = {'b', 'C'};
int octave[] = {3, 3};
int current_step = 0;

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

int calculate_prescaler(long int cycles) {
    if(cycles < 65536) return 0;
    if(cycles/8 < 65536) return 1;
    if(cycles/64 < 65536) return 2;
    return 3;
}

int calculate_PRx (long int cycles, int prescaler) {
    return (cycles / prescaler) -1;
}

void init_speaker(void) {
    TRISBbits.TRISB6 = 0;
    
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR3bits.RP6R = 18;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    OC1CON = 0;
    OC1CONbits.OCTSEL = 0b1;
    OC1CONbits.OCM = 0b110;
    
    T3CON = 0;
    T3CONbits.TCKPS = 0b00;
    TMR3 = 0;
    PR3 = 39999;
    
    T3CONbits.TON = 1;
    OC1R = 19999;
    OC1RS = 19999;
    
    T5CON = 0;
    TMR5 = 0;
    IFS1bits.T5IF = 0;
    IEC1bits.T5IE = 0;
    T5CONbits.TCKPS = 3;
    TMR5 = 0;
    PR5 = 31249;
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
long int note_to_cycles(char note, int octave) {
    int n = note_char_to_int(note);
    if(n == -1) return n;
    
    long int cycles = note_cycles[n];
    for(int i = 1; i < octave; i++) {
        cycles /= 2;
    }
    return cycles;
}

unsigned long int bpm_to_cycles(int bpm) {
    return 960000000 / bpm;
}

// Min tempo = 58, Max tempo > 1,000,000
void set_tempo(int tempo) {
    IEC1bits.T5IE = 0;
    T5CON = 0;
    
    unsigned long int cycles = bpm_to_cycles(tempo);
    int pr5 = calculate_PRx(cycles);
    int prescaler = calculate_prescaler(cycles, pr5);
    
    IFS1bits.T5IF = 0;
    T5CONbits.TCKPS = prescaler;
    TMR5 = 0;
    PR5 = pr5;
    
    //T5CONbits.TON = 1;
    IEC1bits.T5IE = 0;
}

void set_note(char note, int octave) {
    if(note == " ") {
        OC1RS = 0;
        return;
    }
    long int cycles = note_to_cycles(note, octave);
    int pr3 = calculate_PRx(cycles);
    int prescaler = calculate_prescaler(cycles, pr3);
    
    T3CON = 0;
    T3CONbits.TCKPS = prescaler;
    TMR3 = 0;
    PR3 = pr3;
    
    T3CONbits.TON = 1;
    OC1R = pr3 / 2;
    OC1RS = pr3 / 2;
}

/**
 * For each step, set the correct note if the previous note is not still held.
 * @param steps Piece length divided by steps per minute
 * @param tempo steps per minute
 * @return 0 if successful
 */
int play_music(int steps, int tempo) {
    current_step = 0;
    set_tempo(tempo);
    T5CONbits.TON = 1;
    while(current_step < steps) {
        while(_T5IF == 0);
        if(hold[current_step] == 0) 
            set_note(note[current_step], octave[current_step]);
        current_step++;
    }
    return 0;
}