/*
 * File:   FinalProject_LIDARLibrary_v001.c
 * Author: Julian Klemann
 *
 * Created on 13. huhtikuuta 2023, 11:22
 */

#include "xc.h"
#include "FinalProject_LIDARLibrary.h"

void lidar_read_cmd(char command)
{
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | TRANSMIT; /* Address slave for receiving */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0; /* Control byte */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command; /* Command */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);
}

void lidar_write_cmd(char command)
{
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | RECEIVE; /* Address slave for receiving */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0; /* Control byte */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command; /* Command */
    while(!IFS3bits.MI2C2IF);
    
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);
}

void lidar_init(void)
{
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9d;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay_ms(40);
}