/*
 * File:   main.c
 * Author: Yago
 *
 * Created on 20 de Maio de 2016, 03:12
 */

#include <xc.h>
#include <p18f4550.h>
#include "DonPimpolhoBoard.h"
#include "conversorAD.h"
#include "PMW_timer2.h"
#include "PWM_timer0.h"
#include "ReflectanceSensors.h"
#include "serial.h"
#include "averageMoving.h"

#define LIMITE 50

long unsigned int pwm;

void interrupt high_priority ISR() {

    PWMtimer2_B(150);

    PWMtimer0_B(100);

}

void main(void) {

    unsigned int valor , filtered;
    char valorH, valorL, i;
    unsigned long int j;

    TRISD1 = 0;
    TRISD3 = 0;

    TRISB0 = 0;
    TRISC0 = 0;
    
    RC0 = 0;
    
    RD1 = 1;
    RD3 = 1;

    RB0 = 0;

    DonPimpolhoBoard_init();

    serial_config();
        
    


    //    linha_branca();
    TRISD5 = 1;

    for (;;) {

                calibrates_sensors();

        if (RD5) {
            break;
        }
    }

    RC0 = 1;
    
    for (;;) {
        
            read_sensorns(BLACK,55);        

            valor = return_distanceLine();
            
            filtered = moving_avarege(valor);

            enviaSerial('V');
            enviaSerial((valor / 1000) + 48);
            enviaSerial(((valor / 100) % 10) + 48);
            enviaSerial((valor % 100) / 10 + 48);
            enviaSerial((((valor % 1000) % 100) % 10) + 48);
            enviaSerial('F');
            enviaSerial((filtered / 1000) + 48);
            enviaSerial(((filtered / 100) % 10) + 48);
            enviaSerial((filtered % 100) / 10 + 48);
            enviaSerial((((filtered % 1000) % 100) % 10) + 48);
            


        for (j = 0; j < 10000; j++);

    }

}