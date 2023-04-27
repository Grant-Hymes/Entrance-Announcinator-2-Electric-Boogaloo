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

/**
 * Calculates the PRx needed to create the correct period, which is what sets the frequency
 * @param cycles The length of the period in instruction cycles
 * @param prescaler The prescaler mode
 * @return 
 */
int calculate_PRx (long int cycles, int prescaler) {
    if (prescaler == 0) return (cycles / 1) -1;
    if (prescaler == 1) return (cycles / 8) -1;
    if (prescaler == 2) return (cycles / 64) -1;
    return (cycles / 256) -1;
}

/**
 * Initializes output compare 1, which is used to generate a waveform to be sent to a speaker
 * @param pin selects the pin that the speaker / output compare 1 will be mapped to works with pins 6 through 9
 */
void init_speaker(int pin) {
    
    // ensures pin is within 6 to 9
    if (pin < 6 || pin > 9) {
        return;
    }
    
    // assigns output compare 1 to the given pin
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    if (pin == 6) {
        TRISBbits.TRISB6 = 0;
        RPOR3bits.RP6R = 18;
    } else if (pin == 7) {
        TRISBbits.TRISB7 = 0;
        RPOR3bits.RP7R = 18;
    } else if (pin == 8) {
        TRISBbits.TRISB8 = 0;
        RPOR4bits.RP8R = 18;
    } else if (pin == 9) {
        TRISBbits.TRISB9 = 0;
        RPOR4bits.RP9R = 18;
    }
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    // rest of the function sets the output compare 1 control registers
    
    OC1CON = 0;
    OC1CONbits.OCTSEL = 0b1;
    OC1CONbits.OCM = 0b110;
    
    T3CON = 0;
    T3CONbits.TCKPS = 0b00;
    TMR3 = 0;
    PR3 = 39999;
    
    T3CONbits.TON = 1;
    // OC1R and OC1RS should be set to 0 so nothing is playing until the appropriate functions are called
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
 * @param note The char representation of a note. Sharps like C# are not directly represented; the equivalent
 *             flat is used and is noted by a lowercase of the note, eg. D flat is written as d
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

/**
 * Converts a char representation of a number in hex into its integer value
 * @param length char of what is to be converted. The letter values of a (10) through w (32) are supported in either uppercase or lowercase
 * @return int value representation of what length was. 0 is returned by default if the char length is not something
 *         represented in hexadecimal
 */
int length_char_to_int(char length) {
    if (length>='0' && length<='9')
        return length - '0';
    if (length>='a' && length<='w')
        return length + 10 - 'a';
    if (length>='A' && length<='W')
        return length + 10 - 'A';
    return 0;
}

/**
 * Converts a note to its period in 16MHz clock cycles.
 * @param octave Octave number as an int.
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

/**
 * Converts given value for tempo into number based on Tcy in 16 MHz cycles
 * @param bpm int value representing the tempo in beats per minute
 * @return the beats per minute in the number of instruction cycles
 */
unsigned long int bpm_to_cycles(int bpm) {
    return 960000000 / bpm;
}

/**
 * Sets the tempo by changing the appropriate values for T5
 * @param tempo int value representing the desired tempo in beats per minute
 *        The smallest tempo possible is 58 bpm, largest is over 1,000,000 bpm
 */
void set_tempo(int tempo) {
    // Min tempo = 58, Max tempo > 1,000,000
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

/**
 * Calculates and changes the appropriate T3 values to adjust the frequency
 * This will make the note continuously play; it will need to be called again with ' ' input
 * @param note char representation of the note to be played
 * @param octave int value representing the octave the given note should be
 */
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
 * @param s a struct of type Song
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

/**
 * Plays a single note for a given number of seconds
 * @param note Char array with first element representing the note, second element is the octave
 * @param msec Int value for how many seconds to play the note for
 */
void play_note(char note[], int seconds) {
    set_note(note[0], length_char_to_int(note[1]));
    delay_ms2(1000 * seconds);
    set_note(' ', 3);
    
}
