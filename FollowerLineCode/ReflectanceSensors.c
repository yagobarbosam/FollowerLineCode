/*
 * File:   ReflectanceSensors.c
 * Author: Yago
 *
 * Created on 8 de Outubro de 2016, 10:38
 */

//------------------------------------------------
//               Define Adjustable
//------------------------------------------------

#include <p18f4550.h>
#include "ReflectanceSensors.h"
#include "conversorAD.h"

//------------------------------------------------
//               Define Adjustable
//------------------------------------------------

#define LENGHT_BAR 580 // mm
#define NUM_SENSORS 8 
#define LENGHT_SENSOR 27

//------------------------------------------------
//               Define Auxiliary
//------------------------------------------------

#define SPACING_SENSOR LENGHT_BAR/(NUM_SENSORS-1)
#define SPACING_SENSOR_HALF SPACING_SENSOR/2
#define TRESHOLD_SAMPLE 20

//------------------------------------------------
//               Variables Auxiliary
//------------------------------------------------

unsigned int second_portion[NUM_SENSORS];

unsigned int MAX_sensorns[NUM_SENSORS];
unsigned int MIN_sensorns[NUM_SENSORS];

unsigned char sensor_bar[NUM_SENSORS];
unsigned int distance_line = 0;

//------------------------------------------------
//                   Functions 
//------------------------------------------------

void reflectanceSensors_init(void){
    
    unsigned char i;
    
    for(i=0;i < NUM_SENSORS; i++ ){
        MAX_sensorns[i] = 0x0000;
        MIN_sensorns[i] = 0xFFFF;
        
        second_portion[i] = i*SPACING_SENSOR/2;
        
    }
    
}    


void calibrates_sensors(void) {

    unsigned int bar_sensorns[NUM_SENSORS];
    unsigned int i;

    for (i = 0; i < NUM_SENSORS; i++) {

        bar_sensorns[i] = valor_AD(i);

        if (bar_sensorns[i] > MAX_sensorns[i]) {
            MAX_sensorns[i] = bar_sensorns[i];
        }

        if (bar_sensorns[i] < MIN_sensorns[i]) {
            MIN_sensorns[i] = bar_sensorns[i];
        }
    }

}

void read_sensorns(color color_line, unsigned char threshold_value) {

    unsigned char i, max_index = 0, index_over_limit;
    unsigned int var_assist = 0, valueAD;
    unsigned char num_fired = 0, num_over_limit_line = 0;
    unsigned int third_portion;

    for (i = 0; i < NUM_SENSORS; i++) {
        valueAD = valor_AD(i);
        if (valueAD > MAX_sensorns[i]) valueAD = MAX_sensorns[i];
        if (valueAD < MIN_sensorns[i]) valueAD = MIN_sensorns[i];

        var_assist = 64 * (valueAD - MIN_sensorns[i]) / (MAX_sensorns[i] - MIN_sensorns[i]);
        sensor_bar[i] = var_assist; 

        if (color_line == WHITE) {
            sensor_bar[i] = 64 - sensor_bar[i];
        }
        //************************************************************************************************************
        //************************************************************************************************************        

        if (sensor_bar[i] > threshold_value) {
            num_fired++;
            if (max_index < i) {
                max_index = i;
            }
        } else if (sensor_bar[i] > TRESHOLD_SAMPLE) {
            num_over_limit_line++;
            index_over_limit = i;
        }

    }
    third_portion = LENGHT_SENSOR - (LENGHT_SENSOR * sensor_bar[index_over_limit]) / 64;

    if (num_over_limit_line) {
        if (max_index > index_over_limit) {
            distance_line = SPACING_SENSOR * (7 - max_index) + second_portion[num_fired - 1] + SPACING_SENSOR_HALF - third_portion;
        } else {
            distance_line = SPACING_SENSOR * (7 - max_index) + second_portion[num_fired - 1] - SPACING_SENSOR_HALF + third_portion;
        }
    } else {
        distance_line = SPACING_SENSOR * (7 - max_index) + second_portion[num_fired - 1];
    }
}

unsigned int return_distanceLine(void) {

    return distance_line;

}
