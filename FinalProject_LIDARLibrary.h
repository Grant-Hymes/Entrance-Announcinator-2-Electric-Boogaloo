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
};

/* FinalProject_LIDAR_IO_v001 */
char lidar_read_8bit_cmd(uint16_t addr);
uint16_t lidar_read_16bit_cmd(uint16_t addr);
void lidar_write_8bit_cmd(uint16_t addr, char data);
void lidar_write_16bit_cmd(uint16_t addr, uint16_t data);
void lidar_write_32bit_cmd(uint16_t addr, uint32_t data);

/* FinalProject_LIDAR_v001 */
void lidar_start_continuous_measurement(uint32_t period_ms);
void lidar_set_timing_budget_us(uint32_t budget_us);
void lidar_init(void);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* FINALPROJECT_LIDARLIBRARY_H */

