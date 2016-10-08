/* 
 * File:   PMW_timer2.h
 * Author: Yago
 *
 * Created on 21 de Maio de 2016, 10:43
 */

#ifndef PMW_TIMER2_H
#define	PMW_TIMER2_H

void PWMtimer2_48MHzCLK_config(char priority);

void PWMtimer2_on(void);

void PWMtimer2_A_pin(char *port , char *tris , char pino);
void PWMtimer2_A(unsigned char duty);

void PWMtimer2_B_pin(char *port, char *tris, char pino);
void PWMtimer2_B(unsigned char duty);


#define NO_PRIORITY 0
#define HIGH_PRIORITY 1
#define LOW_PRIORITY 2

#endif	/* PMW_TIMER2_H */

