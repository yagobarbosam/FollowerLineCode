/* 
 * File:   encoderMotor.h
 * Author: Yago
 *
 * Created on 11 de Outubro de 2016, 21:52
 */

#ifndef ENCODERMOTOR_H
#define	ENCODERMOTOR_H

typedef enum{ENCODER_RIGHT,ENCODER_LEFT}side;

void encoder_interrupt(void);
void update_speed(void);
unsigned int get_speed(side sideEncoder);
void interrupt_encoder(char enable, char priority);

#endif	/* ENCODERMOTOR_H */

