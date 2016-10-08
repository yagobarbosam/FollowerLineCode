/*
 * File:   ReflectanceSensors.c
 * Author: Yago
 *
 * Created on 4 de Junho de 2016, 10:38
 */

#include <p18f4550.h>
#include "ReflectanceSensors.h"
#include "conversorAD.h"


#define LENGHT_BAR 580 // mm
#define NUM_SENSORS 8 
#define LENGHT_SENSOR 27


#define SPACING_SENSOR LENGHT_BAR/(NUM_SENSORS-1)

#define SPACING_SENSOR_HALF SPACING_SENSOR/2

#define TRESHOLD_SAMPLE 20

unsigned int second_portion[8] = {0, SPACING_SENSOR / 2, SPACING_SENSOR, 3 * SPACING_SENSOR / 2, 2 * SPACING_SENSOR,
    5 * SPACING_SENSOR / 2, 3 * SPACING_SENSOR, 7 * SPACING_SENSOR / 2};



unsigned int MAX_sensorns[8] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
MIN_sensorns[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

unsigned char sensor_bar[8];

unsigned int distance_line = 0;

void calibrates_sensors(void) {

    unsigned int bar_sensorns[8];
    unsigned int i;

    for (i = 0; i < 8; i++) {

        bar_sensorns[i] = valor_AD(i);

        if (bar_sensorns[i] > MAX_sensorns[i]) {
            MAX_sensorns[i] = bar_sensorns[i];
        }

        if (bar_sensorns[i] < MIN_sensorns[i]) {
            MIN_sensorns[i] = bar_sensorns[i];
        }
    }

}

// Seguindo a Documentação

void read_sensorns(color color_line, unsigned char threshold_value) {

    unsigned char i, max_index = 0, index_over_limit;
    unsigned int var_assist = 0, valueAD;
    unsigned char num_fired = 0, num_over_limit_line = 0;
    unsigned int third_portion;

    for (i = 0; i < 8; i++) {
        valueAD = valor_AD(i);
        if (valueAD > MAX_sensorns[i]) valueAD = MAX_sensorns[i];
        if (valueAD < MIN_sensorns[i]) valueAD = MIN_sensorns[i];

        var_assist = 64 * (valueAD - MIN_sensorns[i]) / (MAX_sensorns[i] - MIN_sensorns[i]);
        sensor_bar[i] = var_assist; // Lembrando que estamos igualando um INT com um CHAR

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