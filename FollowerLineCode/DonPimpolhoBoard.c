/*
 * File:   DonPimpolhoBoard.c
 * Author: Yago
 *
 * Created on 20 de Maio de 2016, 01:33
 */
//*********************************************************************************
//COMENTARIO : Abaixo se encontra todas a ligações dos pinos do PIC18F4550 para a
//Placa DonPimpolho 2.1V . Arquivo este deve ser revisado . 
//*********************************************************************************

//--------------------------------------------------------------------------------
//              ARQUIVO DE MAPEAMENTO DE PINOS DO DON PIMPOLHO 2.1V              |
//--------------------------------------------------------------------------------        
//                              **********************                      
//                              *  SENSORES FRENTE   *
//                              ********************** 

//                                 AN4(RA5)  AN3(RA3)        
//                       AN5(RE0)                     AN2(RA2)
//              AN6(RE1)                                        AN1(RA1) 
//     AN7(RE2)                                                           AN0(RA0)

//  TRISA = 0bxx1x1111;
//  TRISE = 0bxxxxx111;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------                                        
//                              **********************                      
//                              * SENSORES  LATERAIS *
//                              **********************

//       SENSOR DA ESQUERDA                                       SENSOR DA DIREITA
//           AN9(RB3)                                                  AN8(RB2)

//  TRISB = 0bxxxx11xx;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//                              ***********************                      
//                              * PINOS DRIVE DRV8833 *
//                              ***********************
//
//              DRIVER ESQUERDA U17                    DRIVER DIREITA U18
//                    RD0(AIN1)                              RD2(BIN1)
//                    RD1(AIN2)                              RD3(BIN2)
//  TRISD = 0bxxxx0000;
///------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//                              ***********************                      
//                              *    PINOS ENCODER    *
//                              ***********************
//
//        ENCODER MOTOR ESQUERDA                                 ENCODER MOTOR DIREITA
//              RB5(ENC_2A)                                           RB4(ENC_2B)
///------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//                              ***********************                      
//                              *  PINOS PERIFERICOS  *
//                              ***********************

//     BUZZ --> RB0          LED --> RC0     VREF_BAT --> RB1         LED_BAT --> RD4
///------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------      

#include <p18f4550.h>
#include "DonPimpolhoBoard.h"
#include "conversorAD.h"
#include "PMW_timer2.h"
#include "PWM_timer0.h"


void DonPimpolhoBoard_init(void) {
   
    conversorAD_config(VCC,GND,AN10);
    
    PWMtimer0_48MHzCLK_config(HIGH_PRIORITY); 
    PWMtimer0_B_pin(&PORTD,&TRISD,2);
    PWMtimer0_on();
        
    PWMtimer2_48MHzCLK_config(HIGH_PRIORITY);    
    PWMtimer2_B_pin(&PORTD,&TRISD,0);
    PWMtimer2_on();   
    
    GIE = 1;       
}





