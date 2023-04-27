/* 
 * File:   FinalProject_MotionSensorLibrary.h
 * Author: gahym
 *
 * Created on April 21, 2023, 11:42 AM
 */

#ifndef FINALPROJECT_MOTIONSENSORLIBRARY_H
#define	FINALPROJECT_MOTIONSENSORLIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    volatile int status;
    volatile int trippedTime;

    void initMotionSensor(int pin);


#ifdef	__cplusplus
}
#endif

#endif	/* FINALPROJECT_MOTIONSENSORLIBRARY_H */

