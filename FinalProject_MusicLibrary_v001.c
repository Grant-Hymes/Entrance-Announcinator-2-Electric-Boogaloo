/*
 * File:   FinalProject_MusicLibrary_v001.c
 * Author: egcar
 *
 * Created on April 13, 2023, 1:46 PM
 */

#include "xc.h"
#include "FinalProject_MusicLibrary.h"
#include <stdlib.h>

/**
 * For each step, update values if needed then play the note
 * @param steps Length divided by smallest note division
 * @return 0 if successful
 */
int play_music(int steps, int tempo) {
    for(int i = 0; i < steps; i++) {
        init_tempo(tempo);
        if(hold[i] == 0) {
            long int cycles = note_to_cycles(note[i], octave[i]);
            overflow_target = cycles_overflows(cycles);
            PRx = cycles_PRx(cycles);
            remainder = cycles_remainder(cycles);
            
        }
        play_note();
        
    }
    
    return 0;
}

// TODO
void play_note() {
    while(1);
}

// TODO
void init_tempo(int tempo) {
    while(1);
}
