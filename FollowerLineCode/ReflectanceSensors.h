/* 
 * File:   ReflectanceSensors.h
 * Author: Yago
 *
 * Created on 8 de Outrubro de 2016, 10:38
 */

#ifndef REFLECTANCESENSORS_H
#define	REFLECTANCESENSORS_H

//----------------------------
//   Auxiliary Constants  
//----------------------------

typedef enum {WHITE, BLACK} color;

//----------------------------
//     Function prototype 
//----------------------------

void reflectanceSensors_init(void);

unsigned int return_distanceLine(void);

void calibrates_sensors(void);

void read_sensorns(color, unsigned char);

//----------------------------

#endif	/* REFLECTANCESENSORS_H */

