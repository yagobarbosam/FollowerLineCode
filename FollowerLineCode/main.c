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
#include "encoderMotor.h"
#include "PID_controlerMotor.h"

#define LIMITE 50

unsigned int pwm;
signed int pwm_1;

unsigned int direita, esquerda;

void interrupt high_priority ISR() {

    PWMtimer2_B(pwm);

    PWMtimer0_B(pwm);

    encoder_interrupt();
    //    update_speed();

}

void main(void) {

    unsigned int valor, filtered;
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

    setup_setpoint(1000);
    setup_PID(0.2, 0, 0);


    //    linha_branca();
    TRISD5 = 1;

    for (;;) {

        calibrates_sensors();

        direita = get_speed(ENCODER_RIGHT);
        esquerda = get_speed(ENCODER_LEFT);

        pwm_1 = PID(direita);
        pwm_1 += 126;
        
        if (pwm_1 <= 0) {
            pwm = 0;
        } else if (pwm_1 >= 255) {
            pwm = 255;
        } else {
            pwm = pwm_1;
        }



//        for (j = 0; j < 10000; j++);

        if (RD5) {
            break;
        }
    }

    RC0 = 1;

    for (;;) {

        read_sensorns(BLACK, 55);

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
