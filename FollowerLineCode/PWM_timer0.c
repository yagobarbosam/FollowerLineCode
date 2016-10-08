

#include <p18f4550.h>
#include "PWM_timer0.h"

#define TOP_INT 65535
#define TOP_RAMPA 12000

#define LARGURA_TOTAL 53535

#define MAX_DUTY 240       
#define MIN_DUTY 10

unsigned char *portA_p0;
unsigned char mask_A;
unsigned int true_duty0_A;

unsigned char *portB_p0;
unsigned char mask_B;
unsigned int true_duty0_B;

void PWMtimer0_48MHzCLK_config(char priority) {

    T0CON &= 0b10111111;
    T0CS = 0;
    T0SE = 0;
    PSA = 1;
//    T0CON = 0b00000111;

    if (priority == NO_PRIORITY) {
    } else if (priority == HIGH_PRIORITY) {
        IPEN = 1;
        TMR0IP = 1;
    } else if (priority == LOW_PRIORITY) {
        IPEN = 1;
        TMR0IP = 0;
    }

}

void PWMtimer0_on(void) {

    TMR0IE = 1;
    TMR0ON = 1;
    TMR0IF = 0;

}

void PWMtimer0_A_pin(char *port, char *tris, char pino) {

    char *tris_p;
    char mask = 1, i;

    for (i = 0; i < pino; i++) {
        mask *= 2;
    }

    mask_A = mask;

    mask = ~mask;

    portA_p0 = port;
    tris_p = tris;

    *tris_p &= mask;

}

//********************************************************************************
//********************************************************************************
//                        (2^16 * Pre-ESC)/48 MHz  = TIME        
//********************************************************************************
//********************************************************************************

void PWMtimer0_A(unsigned char duty) {

    if (TMR0IF) {

        unsigned int time;

        if (duty <= MIN_DUTY) {
            duty = MIN_DUTY;
        } else if (duty >= MAX_DUTY) {
            duty = MAX_DUTY;
        }

        if ((*portA_p0) & mask_A) {
            *portA_p0 &= (~mask_A); // CLR PINO

            time = LARGURA_TOTAL + 48 * duty;
            TMR0H = (time >> 8);
            TMR0L = (time & 0x00FF);

            true_duty0_A = TOP_INT - 48 * duty;
        } else {
            *portA_p0 |= mask_A; // SET PINO

            TMR0H = (true_duty0_A >> 8);
            TMR0L = (true_duty0_A & 0x00FF);
        }


        TMR0IF = 0;
    }

}

void PWMtimer0_B_pin(char *port, char *tris, char pino) {

    char *tris_p;
    char mask = 1, i;

    for (i = 0; i < pino; i++) {
        mask *= 2;
    }

    mask_B = mask;

    mask = ~mask;

    portB_p0 = port;
    tris_p = tris;

    *tris_p &= mask;

}

void PWMtimer0_B(unsigned char duty) {

    if (TMR0IF) {

        unsigned int time;

        if (duty <= MIN_DUTY) {
            duty = MIN_DUTY;
        } else if (duty >= MAX_DUTY) {
            duty = MAX_DUTY;
        }

        if ((*portB_p0) & mask_B) {
            *portB_p0 &= (~mask_B); // CLR PINO

            time = LARGURA_TOTAL + 48 * duty;
            TMR0H = (time >> 8);
            TMR0L = (time & 0x00FF);

            true_duty0_B = TOP_INT - 48 * duty;
        } else {
            *portB_p0 |= mask_B; // SET PINO

            TMR0H = (true_duty0_B >> 8);
            TMR0L = (true_duty0_B & 0x00FF);
        }


        TMR0IF = 0;
    }

}






