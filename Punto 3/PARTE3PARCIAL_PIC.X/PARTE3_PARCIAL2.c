/*
 * File:   main.c (PERSONALIZACIÓN CARACTER)
 * 
 * Autores: Oscar David Poblador Parra      20211005116
 *          Juan David Bello Rodriguez      20211005028 
 *          Manuel Alejandro Guio Cardona   20211005061
 * Intritución: Universidad Distrital Francisco José de Caldas
 */


#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (WDT disabled in hardware (SWDTEN ignored))
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler (1:32768)

#include "Setup.h"
#include "UART.h"
#include "LCD_16x2.h"
//#include "config.h"
#include <stdio.h>
#include <string.h>

int ADC,aux;



unsigned int ReadADC(unsigned char channel) {
    // Configura el canal de entrada
    ADCON0 = (channel << 2) | 0x01; // Configura el canal y habilita el ADC
    GO_nDONE = 1; // Inicia la conversión
    while (GO_nDONE); // Espera a que termine la conversión 
    return ((ADRESH << 8) | ADRESL); // Retorna el resultado de la conversión
}

double VOLTAJE(int ADC){
    double voltaje=0;
    voltaje= (double)ADC*5/1023;
    return voltaje; 
}

void IMPRIMIR(){
    LCD_Clear();
    char imprimir[10]; //Guarda como caracteres el valor del registro prueba
    char imprimir2[30];
    char imprimir3[30]="VOLTAJE: ";
    char imprimir4[30]="V   ";
    char imprimir5[30]="ADRES: ";
    char imprimir6[30]="#";
    aux=ADC;
    
    ADC=ReadADC(10);
    sprintf(imprimir, "%d", ADC);
    LCD_SetCursor(0,0);
    LCD_Text("ADRES: ");
    LCD_SetCursor(0,7);
    LCD_Text(imprimir);
    
    sprintf(imprimir2, "%.2f", VOLTAJE(ADC));
    LCD_SetCursor(1,0);
    LCD_Text("VOLTAJE: ");
    LCD_SetCursor(1,10);
    LCD_Text(imprimir2);
    
    
    
    if(ADC!=aux){
        strcat(imprimir3,imprimir2);
        strcat(imprimir3,imprimir4);
        strcat(imprimir3,imprimir5);
        strcat(imprimir3,imprimir);
        strcat(imprimir3,imprimir6);
        UART_printf(imprimir3);
        UART_printf("\n");
    }
    
    __delay_ms(200);
}


void main(void){
    Setup();
//    UART_init();
    UART_init_baud(9600);
    LCD_Init();
    while(1){
        //UART_printf('d');
        IMPRIMIR();
//        LCD_SetCursor(0,0);
//        LCD_Text("VOLTAJE: ");
    }
} 



