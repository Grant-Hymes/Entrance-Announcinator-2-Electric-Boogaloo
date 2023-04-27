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
    struct Song;
    
    int play_music(struct Song s);
    void set_note(char note, int octave);
    void init_tempo(int tempo);
    void init_speaker(int pin);
    void play_note(char note[], int seconds);
#ifdef	__cplusplus
}
#endif

#endif	/* FINALPROJECT_MUSICLIBRARY_H */

