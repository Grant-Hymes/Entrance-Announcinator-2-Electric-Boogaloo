// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef FINALPROJECT_LIDARLIBRARY_H
#define	FINALPROJECT_LIDARLIBRARY_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
enum {
    LIDAR_ADDR = 0b01010010,
    LIDAR_WRITE = 0,
    LIDAR_READ = 1,
    LIDAR_DEFAULT_TIMING_GUARD = 4528,
    LIDAR_TARGET_DSS_TOTAL_RATE_MCPS = 0x0a00,
};

struct range_results {
    uint8_t range_status; /* 0x0089 */
    uint8_t stream_count; /* 0x008b */
    uint16_t dss_actual_effective_spads_sd0; /* 0x008c */
    uint16_t ambient_count_rate_mcps_sd0; /* 0x008e */
    uint16_t final_crosstalk_corrected_range_mm_sd0; /* 0x0096 */
    uint16_t peak_signal_count_rate_crosstalk_corrected_mcps_sd0; /* 0x0098 */
};


/* FinalProject_LIDAR_IO_v001 */
char lidar_read_8bit_cmd(uint16_t addr);
uint16_t lidar_read_16bit_cmd(uint16_t addr);
void lidar_write_8bit_cmd(uint16_t addr, char data);
void lidar_write_16bit_cmd(uint16_t addr, uint16_t data);
void lidar_write_32bit_cmd(uint16_t addr, uint32_t data);

/* FinalProject_LIDAR_v001 */
void lidar_start_continuous_measurement(uint32_t period_ms);
uint16_t lidar_read_distance(void);
void lidar_set_timing_budget_us(uint32_t budget_us);
void lidar_init(void);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* FINALPROJECT_LIDARLIBRARY_H */

