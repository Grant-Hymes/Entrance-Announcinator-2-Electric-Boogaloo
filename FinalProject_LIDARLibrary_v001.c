/*
 * File:   FinalProject_LIDARLibrary_v001.c
 * Author: Julian Klemann
 *
 * Created on 13. huhtikuuta 2023, 11:22
 */

#include "xc.h"
#include "FinalProject_LIDARLibrary.h"

void lidar_init(void)
{
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9d;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay_ms(5);

    /* TODO: DataInit and StaticInit */
}