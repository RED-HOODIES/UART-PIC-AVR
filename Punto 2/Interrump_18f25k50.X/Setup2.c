#include <xc.h>
#include "Setup.h"

unsigned int Contador=0;

void SetupOscilador(void)
{
    OSCCON = 0b01010010;
return;}

void Setupports(void)
{
    TRISC=0b00000000;
    LATC =0;
//    LED=0;
//    tLED=0;
return;}

void Setupint(void)
{
    INTCONbits.GIE = 1; //Habilita las interrupciones globales
    INTCONbits.PEIE = 1; //Habilita las interrupciones externas perifericas
    return;}

void SetupINTTMR2(void)
{
    PIR1bits.TMR2IF = 0; //Deshabilita bandera TMR2
    PIE1bits.TMR2IE =1; //Habilita el TMR2
    IPR1bits.TMR2IP = 1; //Habilita la interrupción de TMR2 como alta prioridad
    TMR2= 0x00; //Inicializa registro TMR2 en 0
    T2CON = 0b00000110; //Activa TMR2 con Pscaler=1 y Poscaler=1:1
    PR2 = 249; //Carga un valor inicial al PR2 DEPENDE DEL PERIODO REQUERIDO PARA EL PULSO PWM
    return;}

void SetupPWM(void)
{
    CCP1CON = 0b00001111; //Habilita el modo PWM del registro y pone los LSB del CCPR1L en 11
    CCPR1L = 249; //1-255
return;}

void H_ISR(void) //Interrupcion del TMR2
{
    if (TMR2IF) { // Verificar si la interrupción proviene de Timer2
        TMR2IF = 0; // Limpiar la bandera de interrupción de Timer2
            //Hace la subida
        while(CCPR1L>1){
            if(Contador==100){
                Contador=0;
                CCPR1L=CCPR1L-1;
            }
            else{
                Contador=Contador+1;
            }
        }
        
        CCPR1L=1;
        
        while(CCPR1L<249){
            if(Contador==100){
                Contador=0;
                CCPR1L=CCPR1L+1;
            }
            else{
                Contador=Contador+1;
            }
        }
           
        CCPR1L=249;
    }
return;}

void Setup(void)
{
    SetupOscilador();
    Setupports();
    Setupint();
    SetupINTTMR2();
    SetupPWM();
return;}


