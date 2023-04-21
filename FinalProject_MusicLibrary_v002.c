/*
 * File:   FinalProject_MusicLibrary_v002.c
 * Author: pear0836
 *
 * A library to handle playing notes and music correctly
 */


#include "xc.h"
#include <stdlib.h>

/*
 * Things to have in higher level form:
 * 
 * Allowing input of "C3" instead of "C, 3" for the set note
 * Making it easier to notate the length of each note so that it doesn't have to be manually done
 * 
 * + Input is "1C3" with the form {'beats to hold', 'pitch', 'octave'}
 * 
 * Test the possibility of adding a harmony using a second speaker/buzzer
 *      This should be possible by calculating off the PRx value for the main melody
 *      but would just need math from that, other aspects using the timer should be
 *      pretty much the same as the main melody
 */

// cycles = 1 / freq / Tcy
// Octave 1 cycles, assuming Fcy = 16MHz



struct Song {
        int tempo;
        int size;
        char notes[128][3];
    };


/**
 * delays [ms] milliseconds.
 * @param ms milliseconds to delay
 */
void delay_ms2(unsigned int ms) {
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
    if (prescaler == 0) return (cycles / 1) -1;
    if (prescaler == 1) return (cycles / 8) -1;
    if (prescaler == 2) return (cycles / 64) -1;
    return (cycles / 256) -1;
}

void init_speaker(void) {
    TRISBbits.TRISB8 = 0;
    
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR4bits.RP8R = 18;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    OC1CON = 0;
    OC1CONbits.OCTSEL = 0b1;
    OC1CONbits.OCM = 0b110;
    
    T3CON = 0;
    T3CONbits.TCKPS = 0b00;
    TMR3 = 0;
    PR3 = 39999;
    
    T3CONbits.TON = 1;
    OC1R = 0;
    OC1RS = 0;
    
    // T5 is being used to control the music timing
    T5CON = 0;
    TMR5 = 0;
    IFS1bits.T5IF = 0;
    IEC1bits.T5IE = 0;
    T5CONbits.TCKPS = 3;
    TMR5 = 0;
    PR5 = 31249;
}

/**
 * Converts a note from char representation to the period of the note in cycles.
 * @param note The char representation of a note.
 * @return The period of the note in cycles or -1 if not found.
 */
long int note_char_to_int(char note) {
    if(note == 'C') return 489297;
    else if(note == 'd') return 461760;
    else if(note == 'D') return 435849;
    else if(note == 'e') return 411417;
    else if(note == 'E') return 388350;
    else if(note == 'F') return 366552;
    else if(note == 'g') return 345946;
    else if(note == 'G') return 326531;
    else if(note == 'a') return 308226;
    else if(note == 'A') return 290909;
    else if(note == 'b') return 274584;
    else if(note == 'B') return 259151;
    else return -1;
}

int length_char_to_int(char length) {
    if (length>='0' && length<='9')
        return length - '0';
    if (length>='a' && length<='f')
        return length + 10 - 'a';
    if (length>='A' && length<='F')
        return length + 10 - 'A';
    return 0;
}
/**
 * Converts a note to its period in 16MHz clock cycles.
 * @param octave Octave number.
 * @param note char representation of a note 
 * @return The number of clock cycles in the period of the note.
 */
long int note_to_cycles(char note, int octave) {
    long int cycles = note_char_to_int(note);
    if(cycles == -1) return 0;
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
    int prescaler = calculate_prescaler(cycles);
    int pr5 = calculate_PRx(cycles, prescaler);
    
    IFS1bits.T5IF = 0;
    T5CONbits.TCKPS = prescaler;
    TMR5 = 0;
    PR5 = pr5;
    
    //T5CONbits.TON = 1;
    IEC1bits.T5IE = 0;
}

void set_note(char note, int octave) {
    if(note == ' ') { // Sets a silent note by setting a 0% duty cycle
        OC1RS = 0;
        return;
    }
    long int cycles = note_to_cycles(note, octave);
    int prescaler = calculate_prescaler(cycles);
    int pr3 = calculate_PRx(cycles, prescaler);
    
    
    T3CON = 0;
    T3CONbits.TCKPS = prescaler;
    TMR3 = 0;
    PR3 = pr3;
    
    T3CONbits.TON = 1;
    OC1RS = pr3 / 2;
}

/**
 * For each step, set the correct note if the previous note is not still held.
 * @param steps Piece length divided by steps per minute
 * @param tempo steps per minute
 * @return 0 if successful
 */
int play_music(struct Song s) {
    set_tempo(s.tempo);
    T5CONbits.TON = 1;
    for(int i = 0; i < s.size; i++) {
        set_note(s.notes[i][1], length_char_to_int(s.notes[i][2]));
        for(int j = 0; j < (s.notes[i][0] - '0'); j++) {
            while(_T5IF == 0);
            _T5IF = 0;
        }
    }
    return 0;
}