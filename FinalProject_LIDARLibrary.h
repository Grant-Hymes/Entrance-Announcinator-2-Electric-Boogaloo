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
};

/* FinalProject_LIDARIO_v001 */
char lidar_read_8bit_cmd(uint16_t addr);
uint16_t lidar_read_16bit_cmd(uint16_t addr);
void lidar_write_8bit_cmd(uint16_t addr, char data);
void lidar_write_16bit_cmd(uint16_t addr, uint16_t data);

/* FinalProject_LIDAR_v001 */
void lidar_init(void);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* FINALPROJECT_LIDARLIBRARY_H */

