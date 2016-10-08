/*
 * File:   conversorAD.c
 * Author: Yago
 *
 * Created on 20 de Maio de 2016, 02:19
 */


#include <p18f4550.h>
#include <xc.h>
#include "conversorAD.h"

void conversorAD_config(char pos, char neg , unsigned char chanel) {
    
    char *port_an[13];
    char port_mask[13] = {0x01,0x02,0x04,0x08,0x20,0x01,0x02,0x04,0x04,0x08,0x02,0x10,0x01};
    char i;
        
    port_an[AN0] = &TRISA; port_an[AN1] = &TRISA; port_an[AN2] = &TRISA; port_an[AN3] = &TRISA;
    port_an[AN4] = &TRISA; port_an[AN5] = &TRISE; port_an[AN6] = &TRISE; port_an[AN7] = &TRISE;
    port_an[AN8] = &TRISB; port_an[AN9] = &TRISB; port_an[AN10] = &TRISB; port_an[AN11] = &TRISB;
    port_an[AN12] = &TRISB; 
    
    
    if(pos){
        ADCON1 &= 0b11101111;  // Clear BIT 4
    }else{
        ADCON1 |= 0b00010000; // Set BIT 4
    }
    
    if(neg){
        ADCON1 &= 0b11011111;  // Clear BIT 5
    }else{
        ADCON1 |= 0b00100000; // Set BIT 5
    }
        
    for(i=0;i<=chanel;i++){
        *port_an[i] |= port_mask[i];
    }
    
    chanel = ~chanel - 1;                 // Tabela invertida de ANALOGICO E DIGITAL    
    chanel &= 0b00001111;             // Deleta os ultimos 4 bits
    
    ADCON1 &= 0b11110000;             // Deleta os primeiro 4 bits
    ADCON1 = (ADCON1|chanel);         // Colocar os 4 bits de chanel para o ADCON1
    
    ADFM = 1;                         // Justificado Direita
    
    ADCS2 = 0;                        // FOR 48 MHz Fosc/64
    ADCS1 = 1;
    ADCS0 = 0;
    
    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 1;  
       
}

unsigned int valor_AD(unsigned char chanel){
    
    unsigned int ADvalor = 0;
    
    chanel <<= 2;
    chanel &= 0b00111100;
    ADCON0 &= 0b11000011;
    ADCON0 |= chanel;
    
    ADON = 1;
    
    GO = 1;
    
    while(DONE);
    
    ADvalor = ADRESH;
    ADvalor <<= 8;
    ADvalor += ADRESL;
    
    ADON = 0;
    
    return ADvalor;    
    
}