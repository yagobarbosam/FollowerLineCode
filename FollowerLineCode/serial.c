/*
 * File:   serial.c
 * Author: Yago
 *
 * Created on 4 de Junho de 2016, 17:00
 */

#include <p18f4550.h>
#include "serial.h"

void serial_config(void) {

    TXSTA = 0b00101100; //configura a transmissão de dados da serial
    RCSTA = 0b10010000; //configura a recepção de dados da serial
    BAUDCON = 0b00001000; //configura sistema de velocidade da serial
    SYNC = 0;
    BRGH = 1;
    BRG16 = 1;    
    SPBRGH = 0b00000000; //configura para 56k
    SPBRG = 86; //configura para 56k
    TRISC7 = 0; 
    TRISC6 = 1;
}


void enviaSerial(unsigned char c) {
    while (!TXIF); //aguarda o registro ficar disponível
    TXREG = c; //coloca o valor para ser enviado
}

unsigned char recebeSerial(void) {
    char resp = 0;

    if (OERR) //Verifica se há erro de overrun e reseta a serial
    {
        CREN = 0;
        CREN = 1;
    }

    if (SREN) //Verifica se existe algum valor disponivel
    {
        resp = RCREG; //retorna o valor
    }
    return resp; //retorna zero


}


        