/* 
 * File:   FinalProject_MusicLibrary.h
 * Author: egcar
 *
 * Created on April 13, 2023, 1:46 PM
 */

#ifndef FINALPROJECT_MUSICLIBRARY_H
#define	FINALPROJECT_MUSICLIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif
    //Example
//    int hold[] = {0, 1};
//    char note[] = {'b', 'C'};
//    int octave[] = {3, 3};

//    static int PRx;
//    static int overflow_target;
//    static int remainder;
    
    void set_song(int lhold[], char lnote[], int loctave[], int size);
    int play_music(int steps, int tempo);
    void set_note(char note, int octave);
    void init_tempo(int tempo);
    void init_speaker(void);
#ifdef	__cplusplus
}
#endif

#endif	/* FINALPROJECT_MUSICLIBRARY_H */

