/*
 * File:   FinalProject_LIDARLibrary_v001.c
 * Author: Julian Klemann
 *
 * Created on 13. huhtikuuta 2023, 11:22
 */

#include "xc.h"
#include <stdlib.h>
#include "FinalProject_LIDARLibrary.h"

static uint16_t osc_frequency, osc_calibration;

void delay_ms(unsigned int ms)
{
    while(ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}

uint32_t lidar_timeout_mclks_to_us(uint32_t timeout_mclks, uint32_t macro_period_us)
{
    return ((uint64_t) timeout_mclks * macro_period_us + 0x800) >> 12;
}

uint32_t lidar_timeout_us_to_mclks(uint32_t timeout_us, uint32_t macro_period_us)
{
    return (((uint32_t) timeout_us << 12) + (macro_period_us >> 1)) / macro_period_us;
}

uint32_t lidar_calc_macro_period_us(uint16_t osc_frequency, uint8_t vcsel_period)
{
    uint32_t pll_period_us = ((uint32_t)0x01 << 30) / osc_frequency;

    uint8_t vcsel_period_pclks = (vcsel_period + 1) << 1;
    uint32_t macro_period_us = (uint32_t)2304 * pll_period_us;
    macro_period_us >>= 6;
    macro_period_us *= vcsel_period_pclks;
	macro_period_us = macro_period_us >> 6;

    return macro_period_us;
}

uint16_t lidar_encode_timeout(uint32_t timeout_mclks)
{
    uint32_t encoded_timeout = 0, ls_byte = 0;
    uint16_t ms_byte = 0;

    if (timeout_mclks > 0) {
		ls_byte = timeout_mclks - 1;

		while ((ls_byte & 0xFFFFFF00) > 0) {
			ls_byte = ls_byte >> 1;
			ms_byte++;
		}

		encoded_timeout = (ms_byte << 8)
				+ (uint16_t) (ls_byte & 0x000000FF);
	}

	return encoded_timeout;
}

uint16_t lidar_calc_encoded_timeout(uint32_t timeout_us, uint32_t macro_period_us)
{
    uint32_t timeout_mclks = 0;
	uint16_t encoded_timeout = 0;

	timeout_mclks = ((timeout_us << 12) + (macro_period_us >> 1))
                    / macro_period_us;
    encoded_timeout = lidar_encode_timeout(timeout_mclks);

	return encoded_timeout;
}

void lidar_set_timing_budget_us(uint32_t budget_us)
{
    uint32_t range_config_timeout_us, macro_period_us, phase_timeout_mclks;

    range_config_timeout_us = (budget_us - LIDAR_DEFAULT_TIMING_GUARD) / 2;

    /* VCSEL Period A */
    macro_period_us = lidar_calc_macro_period_us(osc_frequency, 0x0B);

    phase_timeout_mclks = lidar_timeout_us_to_mclks(1000, macro_period_us);
    if (phase_timeout_mclks > 0xFF)
		phase_timeout_mclks = 0xFF;
    lidar_write_8bit_cmd(0x004b, 0xFF /* (char) phase_timeout_mclks */);

    /* MM Timing A */
    lidar_write_16bit_cmd(
        0x005a,
        lidar_calc_encoded_timeout(1, macro_period_us)
    );

    /* Range Timing A */
    lidar_write_16bit_cmd(
        0x005e,
        lidar_calc_encoded_timeout(range_config_timeout_us, macro_period_us)
    );

    /* VCSEL Period B */
    macro_period_us = lidar_calc_macro_period_us(osc_frequency, 0x09);

    /* MM Timing B */
    lidar_write_16bit_cmd(
        0x005c,
        lidar_calc_encoded_timeout(1, macro_period_us)
    );

    /* Range Timing B */
    lidar_write_16bit_cmd(
        0x0061,
        lidar_calc_encoded_timeout(range_config_timeout_us, macro_period_us)
    );
}

void lidar_start_continuous_measurement(uint32_t period_ms)
{
    lidar_write_32bit_cmd(0x006c, period_ms * osc_calibration); /* Intermeasure period */
    lidar_write_8bit_cmd(0x0086, 0x01); /* Clear range interrupt */
    lidar_write_8bit_cmd(0x0087, 0x40); /* Start interrupt, timed mode */
}

void lidar_init(void)
{
    uint16_t outer_offset;

    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9d;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    delay_ms(5);

    /* Soft reset */
    lidar_write_8bit_cmd(0x0000, 0x00);
    delay_ms(1);
    lidar_write_8bit_cmd(0x0000, 0x01);
    delay_ms(1);

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

    lidar_set_timing_budget_us(100000); /* Timing measurement budget of 100 ms */

    /* Initialize range outer offsets */
    outer_offset = lidar_read_16bit_cmd(0x0022);
    lidar_write_16bit_cmd(0x001e, outer_offset * 4);
}