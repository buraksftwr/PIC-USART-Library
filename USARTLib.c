#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "USARTLib.h"

void USARTInit(uint16_t baudrate, uint8_t mode){
	if(baudrate == 1200) // SPBRG bit is configured for 4 MHz crystal oscillator
	        SPBRG = 207;               
	    else if(baudrate == 2400)
	        SPBRG = 103;                
	    else if(baudrate == 9600)
	        SPBRG = 25;               
	    else if(baudrate == 19200)
	        SPBRG = 12;               
	    else if(baudrate == 28800)
	        SPBRG = 8;               
	    else if(baudrate == 33600)
	        SPBRG = 6;
	    else
	        SPBRG = 0; 
	        
    switch(mode){	// The code is configured to operate in asynchronous high speed mode
        case 0: // Both transmit and receive mode is selected
            TXSTA = 0x24;
            RCSTA = 0x90;
            break;
        case 1: // Transmit only mode is selected
            TXSTA = 0x24;
            RCSTA = 0x80;
            break;
        case 2: // Receive only mode is selected
            TXSTA = 0x04;
            RCSTA = 0x90;
            break;    
        default:
            break;
    }
    
}

void USARTSendChar(uint8_t c){
    while(!TRMT);
    TXREG = c;
}

void USARTSendString(unsigned char *str){
    while(*str){
        while(!TRMT);
        USARTSendChar(*str);
        *str++;
    }
}

uint8_t USARTReadChar(void){
    while(!RCIF);
    return RCREG;
}
