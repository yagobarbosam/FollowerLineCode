/* 
 * File:   PWM_timer0.h
 * Author: Yago
 *
 * Created on 1 de Junho de 2016, 00:31
 */

#ifndef PWM_TIMER0_H
#define	PWM_TIMER0_H

void PWMtimer0_48MHzCLK_config(char priority);

void PWMtimer0_on(void);

void PWMtimer0_A_pin(char *port , char *tris , char pino);
void PWMtimer0_A(unsigned char duty);

void PWMtimer0_B_pin(char *port, char *tris, char pino);
void PWMtimer0_B(unsigned char duty);


#endif	/* PWM_TIMER0_H */

