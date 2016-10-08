/*
 * File:   PMW_timer2.c
 * Author: Yago
 *
 * Created on 21 de Maio de 2016, 10:43
 */

//***************************************************************************
//* OBS: PWM COM FREQUENCIA FIXA DE 4KHz E COM VALORES DE DUTY DE 0 --> 255 *
//***************************************************************************

#include <p18f4550.h>
#include "PMW_timer2.h"

#define MAX_PR2 250

#define MAX_DUTY 240       
#define MIN_DUTY 10

unsigned char *portA_p;
unsigned char mask_A2;
unsigned char true_duty_A;

unsigned char *portB_p;
unsigned char mask_B2;
unsigned char true_duty_B;


void PWMtimer2_48MHzCLK_config(char priority) {

    T2CON = 0b00010011; //  POST 3 PRE ESCALE 16

    if (priority == NO_PRIORITY) {
    } else if (priority == HIGH_PRIORITY) {
        IPEN = 1;
        TMR2IP = 1;
    } else if (priority == LOW_PRIORITY) {
        IPEN = 1;
        TMR2IP = 0;
    }
    
}

void PWMtimer2_on(void) {

    TMR2IE = 1;
    TMR2ON = 1;
    TMR2IF = 0;

}

void PWMtimer2_A_pin(char *port, char *tris, char pino) {

    char *tris_p;
    char mask = 1, i;

    for (i = 0; i < pino; i++) {
        mask *= 2;
    }

    mask_A2 = mask;

    mask = ~mask;

    portA_p = port;
    tris_p = tris;

    *tris_p &= mask;

}

void PWMtimer2_A(unsigned char duty) {

    if (TMR2IF) {
        
        if(duty <= MIN_DUTY){
            duty = MIN_DUTY;
        }else if(duty >= MAX_DUTY){
            duty = MAX_DUTY;
        }        
        
        
        if ((*portA_p) & mask_A2) {
            *portA_p &= (~mask_A2); // CLR PINO

            PR2 = MAX_PR2 - duty;
            true_duty_A = duty;
        } else {
            *portA_p |= mask_A2; // SET PINO

            PR2 = true_duty_A;
        }


        TMR2IF = 0;
    }

}

void PWMtimer2_B_pin(char *port, char *tris, char pino) {

    char *tris_p;
    char mask = 1, i;

    for (i = 0; i < pino; i++) {
        mask *= 2;
    }

    mask_B2 = mask;

    mask = ~mask;

    portB_p = port;
    tris_p = tris;

    *tris_p &= mask;

}

void PWMtimer2_B(unsigned char duty) {

    if (TMR2IF) {
        
        if(duty <= MIN_DUTY){
            duty = MIN_DUTY;
        }else if(duty >= MAX_DUTY){
            duty = MAX_DUTY;
        }        
        
        
        if ((*portB_p) & mask_B2) {
            *portB_p &= (~mask_B2); // CLR PINO

            PR2 = MAX_PR2 - duty;
            true_duty_B = duty;
        } else {
            *portB_p |= mask_B2; // SET PINO

            PR2 = true_duty_B;
        }


        TMR2IF = 0;
    }

}