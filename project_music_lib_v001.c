/*
 * File:   project_music_lib_v001.c
 * Author: pear0836
 *
 * A library to handle playing notes correctly
 */


#include "xc.h"
#include <stdlib.h>
//#include "project_utils_lib_v001.h"

//Example
int hold[] = {0, 1};
char note[] = {'b', 'C'};
int octave[] = {3, 3};

static int PRx;
static int overflow_target;
static int remainder;

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