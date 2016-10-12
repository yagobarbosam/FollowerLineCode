/* 
 * File:   PID_controlerMotor.h
 * Author: Yago
 *
 * Created on 12 de Outubro de 2016, 11:31
 */

#ifndef PID_CONTROLERMOTOR_H
#define	PID_CONTROLERMOTOR_H

void setup_setpoint(signed int);

void setup_PID(signed float, signed float, signed float);

void restart_PID(void);

signed int PID(signed int);

#endif	/* PID_CONTROLERMOTOR_H */

