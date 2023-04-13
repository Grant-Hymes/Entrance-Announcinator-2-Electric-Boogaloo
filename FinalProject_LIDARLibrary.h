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
    RECEIVE = 0,
    TRANSMIT = 1,
};

void lidar_read_cmd(char command);
void lidar_write_cmd(char command);

void lidar_set_cursor(char x, char y);
void lidar_shift_right(void);

void lidar_print_char(char data);
void lidar_print_string(char *data);

void lidar_init(void);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* FINALPROJECT_ASMLIBRARY_H */

