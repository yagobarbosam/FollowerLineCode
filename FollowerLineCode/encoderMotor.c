/*
 * File:   encoderMotor.c
 * Author: Yago
 *
 * Created on 11 de Outubro de 2016, 01:33
 */
#include <p18f4550.h>
#include "encoderMotor.h"
#include "defineNames.h"

#define ENCR RB4                   // PINO CANAL 1 DO RECPTOR
#define ENCL RB5                   // PINO CANAL 2 DO RECPTOR
#define TMR_READ TMR1 
#define NULL 0
#define LIMIT_16BIT 65535

typedef struct {
    unsigned int pulse;
    unsigned int risingEdge;
    unsigned int fallingEdge;
    unsigned long int rotation;
    unsigned char state;
    unsigned char state_old;
} encoder;

encoder right, left;

void encoder_init(void) {

    right.state = 0;
    right.state_old = 0;

    left.state = 0;
    left.state_old = 0;
    //    ----------------------------
    //    Inicializa TIMER 1
    //    ----------------------------
    T1CON |= (1 << 7);
    T1CKPS1 = 0; //Pre-scale 2:1 Periodo de 0.0262
    T1CKPS0 = 1;
    TMR1ON = 0;
    //    ----------------------------
    //    Inicializa PORTB
    //    ----------------------------
    TRISB4 = 1;
    TRISB5 = 1;

}

void interrupt_encoder(char enable, char priority) {

    if (priority == NO_PRIORITY) {
    } else if (priority == HIGH_PRIORITY) {
        IPEN = 1;
        TMR1IP = 1;
        RBIP = 1;
    } else if (priority == LOW_PRIORITY) {
        IPEN = 1;
        TMR1IP = 0;
        RBIP = 0;
    }

    if (enable == ENABLE) {
        //        TMR1IE = 1;
        TMR1ON = 1;
        TMR1H = 0x00;
        TMR1L = 0x00;
        RBIE = 1;
    } else if (enable == DISABLE) {
        TMR1IE = 0;
        TMR1ON = 0;
        RBIE = 0;
    }
}

void encoder_interrupt(void) {

    if (RBIF) {

        right.state = ENCR;
        if (right.state != right.state_old) {
            right.state_old = right.state;

            if (right.state) {
                //                right.pulse++;
                right.risingEdge = TMR1;
            } else {

                right.fallingEdge = TMR1;

                if (right.fallingEdge >= right.risingEdge) {

                    right.rotation = right.fallingEdge - right.risingEdge;

                } else {

                    right.rotation = LIMIT_16BIT - right.risingEdge;
                    right.rotation += right.fallingEdge;
                }

            }
        }

        left.state = ENCL;

        if (left.state != left.state_old) {
            left.state_old = left.state;

            if (left.state) {
                //                left.pulse++;
                left.risingEdge = TMR1;

            } else {

                left.fallingEdge = TMR1;

                if (left.fallingEdge >= left.risingEdge) {

                    left.rotation = left.fallingEdge - left.risingEdge;
                } else {

                    left.rotation = LIMIT_16BIT - left.risingEdge;
                    left.rotation += left.fallingEdge;
                }

            }
        }

        RBIF = 0;
    }

}

void update_speed(void) {

    if (TMR1IF) {

        TMR1ON = 0;
        RBIE = 0;
        right.rotation = right.pulse * 100; // (pulse * 2) / 20 [ms] 
        left.rotation = left.pulse * 100; // (pulse * 2) / 20 [ms]

        right.pulse = 0;
        left.pulse = 0;
        TMR1H = 0x3C;
        TMR1L = 0xAF;
        TMR1ON = 1;
        RBIE = 1;

        TMR1IF = 0;

    }

}

unsigned long int get_speed(side sideEncoder) {

    if (sideEncoder == ENCODER_RIGHT) {
        
        right.rotation *= 8;
        right.rotation = 10000000 / right.rotation;
        return right.rotation;
        
    } else if (sideEncoder == ENCODER_LEFT) {

        left.rotation *= 8;
        left.rotation = 10000000 / left.rotation;
        return left.rotation;
        
    } else {
        return NULL;
    }

}



