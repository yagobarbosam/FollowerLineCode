/* 
 * File:   ReflectanceSensors.h
 * Author: Yago
 *
 * Created on 4 de Junho de 2016, 10:38
 */

#ifndef REFLECTANCESENSORS_H
#define	REFLECTANCESENSORS_H

typedef enum {
    WHITE, BLACK
} color;

unsigned int return_distanceLine(void);

void calibrates_sensors(void);
void read_sensorns(color, unsigned char);

#endif	/* REFLECTANCESENSORS_H */

