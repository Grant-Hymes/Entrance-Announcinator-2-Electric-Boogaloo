/*
 * File:   FinalProject_LIDARLIOibrary_v001.c
 * Author: Julian Klemann
 *
 * Created on 13. huhtikuuta 2023, 11:22
 */

#include "xc.h"
#include "FinalProject_LIDARLibrary.h"

char lidar_read_8bit_cmd(uint16_t addr)
{
    char ret;

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_WRITE; /* Address slave for writing */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) (addr >> 8); /* Upper address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) addr; /* Lower address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_READ; /* Address slave for writing */
    while(!IFS3bits.MI2C2IF);

    while(I2C2CON & 0x1f);
    I2C2CONbits.RCEN = 1;
    while(!I2C2STATbits.RBF); /* Read slave data */
    ret = I2C2RCV;
    I2C2CONbits.ACKEN = 1;
    while(!IFS3bits.MI2C2IF); /* Acknowledge */

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);

    return ret;
}

uint16_t lidar_read_16bit_cmd(uint16_t addr)
{
    uint16_t ret;

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_WRITE; /* Address slave for writing */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) (addr >> 8); /* Upper address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) addr; /* Lower address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_READ; /* Address slave for reading */
    while(!IFS3bits.MI2C2IF);

    while(I2C2CON & 0x1f);
    I2C2CONbits.RCEN = 1;
    while(!I2C2STATbits.RBF); /* Read slave data upper */
    ret = (uint16_t) I2C2RCV << 8;
    I2C2CONbits.ACKEN = 1;
    while(!IFS3bits.MI2C2IF); /* Acknowledge */

    while(I2C2CON & 0x1f);
    I2C2CONbits.RCEN = 1;
    while(!I2C2STATbits.RBF); /* Read slave data lower */
    ret |= I2C2RCV;
    I2C2CONbits.ACKEN = 1;
    while(!IFS3bits.MI2C2IF); /* Acknowledge */

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);

    return ret;
}

void lidar_write_8bit_cmd(uint16_t addr, char data)
{
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_WRITE; /* Address slave for writing */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) (addr >> 8); /* Upper address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) addr; /* Lower address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = data; /* Data */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);
}

void lidar_write_16bit_cmd(uint16_t addr, uint16_t data)
{
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1; /* Start bit */
    while(I2C2CONbits.SEN);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = LIDAR_ADDR | LIDAR_WRITE; /* Address slave for writing */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) (addr >> 8); /* Upper address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) addr; /* Lower address */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) (data >> 8); /* Data upper */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2TRN = (char) data; /* Data lower */
    while(!IFS3bits.MI2C2IF);

    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; /* Stop */
    while(I2C2CONbits.PEN);
}