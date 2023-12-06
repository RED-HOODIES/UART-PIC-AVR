/*
-----------------------------------------------------------
                       ATMEGA32U4
-----------------------------------------------------------
 */
#define F_CPU 8000000
#include "UART.h"
#include "Setup.h"
#include <util/delay.h>

#include <string.h>

#include <stdio.h>

#include <avr/interrupt.h>




char RxBuffer[15];
volatile unsigned char RxContador =0;



int main(void)
{

	DDRB |= (1<<5);
   
	
    UART_init(9600);


    
    while (1){ 
        PORTB |= (1<<5);
        UART_printf("Led off  ");
        _delay_ms(1500);
        UART_printf("Led on  ");
        PORTB &= ~(1<<5);
        _delay_ms(1500);
      
    }
    
	
}
