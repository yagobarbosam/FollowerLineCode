/* 
 * File:   conversorAD.h
 * Author: Yago
 *
 * Created on 20 de Maio de 2016, 02:19
 */

#ifndef CONVERSORAD_H
#define	CONVERSORAD_H

void conversorAD_config(char pos, char neg, unsigned char chanel);

unsigned int valor_AD(unsigned char chanel);

#define VDD 1 
#define VCC 1
#define VSS 1
#define GND 1
#define VREF_MORE 0
#define VREF_LESS 0

#define RIGHT_JUSTIFIED 1
#define LEFT_JUSTIFIED 0 

#define AN0 0
#define AN1 1
#define AN2 2
#define AN3 3
#define AN4 4
#define AN5 5
#define AN6 6 
#define AN7 7
#define AN8 8
#define AN9 9
#define AN10 10
#define AN11 11
#define AN12 12



#endif	/* CONVERSORAD_H */

