/*
 * File:   main.c (PERSONALIZACIÓN CARACTER)
 * 
 * Autores: Oscar David Poblador Parra      20211005116
 *          Juan David Bello Rodriguez      20211005028 
 *          Manuel Alejandro Guio Cardona   20211005061
 * Intritución: Universidad Distrital Francisco José de Caldas
 */

#define F_CPU 16000000
#define SALTO (UART_caracter('\r'))

#include "UART.h"
#include "Setup.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

int Brillo,aux;
double porcentaje;
char imprimir[30];
char imprimir2[30];
int S=1,e=1;
char RxBuffer[30];
volatile unsigned char RxContador =0;
char dato;

int DEBOUNCER() {
    if (BOTON) { // Verificar si el botón está presionado (lógica negada debido al resistor pull-up)
        _delay_ms(10); // Pequeño retardo para evitar rebotes
        if (BOTON) { // Verificar nuevamente después del retardo
            return 1; // Botón presionado
        }
    }
    return 0; // Botón no presionado
}

uint16_t ADC_read(uint8_t canal) {
    ADMUX = (ADMUX & 0xF8) | (canal & 0x07); // Configura el canal de ADC a leer
    ADCSRA |= (1 << ADSC); // Inicia la conversión
    while (ADCSRA & (1 << ADSC)); // Espera a que la conversión se complete
    return ADC; // Retorna el valor convertido
}

void IMPRIMIR2(){
    
    sprintf(imprimir, "%s", "____________________________");
    UART_printf("\n");
    UART_printf(imprimir);
    UART_printf("\n");
    sprintf(imprimir, "%s", "O");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "P");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "A");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "C");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "I");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "D");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "A");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "D:");
    UART_printf(imprimir);
    sprintf(imprimir, "%s", " ");
    UART_printf(imprimir);
    sprintf(imprimir, "%.2f", porcentaje);
    UART_printf(imprimir);
    sprintf(imprimir, "%s", "%");
    UART_printf(imprimir);
    UART_printf("\n");
    UART_printf(imprimir2);
    UART_printf("\n");
    sprintf(imprimir, "%s", "____________________________");
    UART_printf(imprimir);
    S=0;
}


void IMPRIMIR(){
    aux=Brillo;
    Brillo=ADC_read(0);
    _delay_ms(25);
    if((Brillo!=(aux+0.01))&&(Brillo!=(aux-0.01)&&(Brillo!=(aux)))){
        porcentaje=(double)Brillo*100/1023;
        S=1;
    }
    
    if(S){
        if(e==1){
            _delay_ms(100);
            e=0;
        }
        IMPRIMIR2();
    }
}

ISR(USART1_RX_vect){
    
    dato = UDR1;
    if(dato == '#'){
        RxBuffer[RxContador] = '\0';
        RxContador = 0;
        for(int i=0;i<30;i++){
            imprimir2[i]=RxBuffer[i];
        }
        
        if(S){
            IMPRIMIR2();
        }
        
        S=1;
    }else{
        RxBuffer[RxContador++] = dato;
    }
	
}

int main(){
    cli();
    UART_init(9600);
    Setup();
    S=1;
    sei();
    while(1){
    IMPRIMIR();
//    aux=Brillo;
//    Brillo=ADC_read(0);
//    porcentaje=(double)Brillo*100/1023;
//    sprintf(imprimir, "%.3f", porcentaje);
//    UART_printf(imprimir);
//    UART_printf("\n");
//    _delay_ms(1000);
    }
}

