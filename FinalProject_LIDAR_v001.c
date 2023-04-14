/*
 * File:   FinalProject_LIDARLibrary_v001.c
 * Author: Julian Klemann
 *
 * Created on 13. huhtikuuta 2023, 11:22
 */

#include "xc.h"
#include "FinalProject_LIDARLibrary.h"

static uint16_t osc_frequency, osc_calibration;

void delay_ms(unsigned int ms)
{
    while(ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}

void lidar_set_timing_budget_ms(unsigned int ms)
{

}

void lidar_init(void)
{
    uint16_t outer_offset;

    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9d;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;

    delay_ms(5);

    osc_frequency = lidar_read_16bit_cmd(0x0006);
    osc_calibration = lidar_read_16bit_cmd(0x00de);

    /* Ranging setup */
    lidar_write_16bit_cmd(0x0024, 0x0a00); /* Total rate reset */
    lidar_write_8bit_cmd(0x0031, 0x02); /* Reset GPIO status */
    lidar_write_8bit_cmd(0x0036, 8); /* Set effective pulse width (ns) */
    lidar_write_8bit_cmd(0x0037, 16); /* Set effective ambient width (ns) */
    lidar_write_8bit_cmd(0x0039, 0x01); /* Compensation valid height (mm) */
    lidar_write_8bit_cmd(0x003e, 0xFF); /* Ignore valid height (mm) */
    lidar_write_8bit_cmd(0x003f, 0); /* Default min clip */
    lidar_write_8bit_cmd(0x0040, 2); /* Default consistency check tolerance */

    lidar_write_16bit_cmd(0x0050, 0x0000); /* Default thresh rate */
    lidar_write_16bit_cmd(0x0052, 0x0000);
    lidar_write_8bit_cmd(0x0057, 0x38); /* Default aperature attentuation */

    /* Default timings, configured later maybe? */
    lidar_write_16bit_cmd(0x0064, 360); /* Sigma thresh */
    lidar_write_16bit_cmd(0x0066, 192); /* Min range rate (MC/S) */

    lidar_write_8bit_cmd(0x0071, 0x01); /* Grouped parameter hold set */
    lidar_write_8bit_cmd(0x007c, 0x01);
    lidar_write_8bit_cmd(0x007e, 2); /* Default quantifier */

    lidar_write_8bit_cmd(0x0082, 0x00); /* Grouped parameter hold unset */
    lidar_write_8bit_cmd(0x0077, 1); /* Default seed config */

    // Configure low power auto mode */
    lidar_write_8bit_cmd(0x0081, 0x8B); /* Sequence config:  VHV, PHASECAL, DSS1, RANGE */
    lidar_write_16bit_cmd(0x0054, 200 << 8); /* Effective SPADs select */
    lidar_write_8bit_cmd(0x004f, 2); /* Set requested active SPADs */

    /* Short ranging mode (better ambient lighting resistance) */
    lidar_write_8bit_cmd(0x0060, 0x07);
    lidar_write_8bit_cmd(0x0063, 0x05);
    lidar_write_8bit_cmd(0x0069, 0x38); /* nice */

    lidar_write_8bit_cmd(0x0078, 0x07);
    lidar_write_8bit_cmd(0x0079, 0x05);
    lidar_write_8bit_cmd(0x007a, 6);
    lidar_write_8bit_cmd(0x007b, 6);

    /* TODO: Timing Budget of 100 ms */

    /* Initialize range outer offsets */
    outer_offset = lidar_read_16bit_cmd(0x0022);
    lidar_write_16bit_cmd(0x001e, outer_offset * 4);
    __builtin_nop();
}