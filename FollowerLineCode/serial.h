/* 
 * File:   serial.h
 * Author: Yago
 *
 * Created on 4 de Junho de 2016, 17:03
 */

#ifndef SERIAL_H
#define	SERIAL_H

void serial_config(void);

void enviaSerial(unsigned char c);
unsigned char recebeSerial(void);

#endif	/* SERIAL_H */

