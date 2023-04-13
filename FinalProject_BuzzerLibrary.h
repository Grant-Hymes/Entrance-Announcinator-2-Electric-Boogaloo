/* 
 * File:   BuzzerLibrary.h
 * Author: egcar
 *
 * Created on April 12, 2023, 1:25 PM
 */


#ifndef BUZZERLIBRARY_H
#define	BUZZERLIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif
    #define PRESCALER 1

    // Assuming 16MHz
    static unsigned long int note_cycles[] {489297, 461760, 435849, 411417, 388350, 
                            366552, 345946, 326531, 308226, 290909, 274584, 259151};
    void delay_ms(unsigned int ms);
    int note_char_to_int(char note);
    int note_to_cycles(char note, int octave);
    int cycles_remainder (long int cycles);
    int cycles_overflows (long int cycles);
    int cycles_PRx (long int cycles);
    void playNote(char note);
#ifdef	__cplusplus
}
#endif

#endif	/* BUZZERLIBRARY_H */

