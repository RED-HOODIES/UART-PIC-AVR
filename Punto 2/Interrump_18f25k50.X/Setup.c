

#include <xc.h>
#include "Setup.h"



void SetupOscilador(void)
{
    OSCCON = 0b01110110;
return;}

void Setupports(void)
{
    TRISC=0b00000000;
    LATC =0;
   
return;}

void Setupint(void)
{
    INTCONbits.GIE = 1; //Habilita las interrupciones globales
    INTCONbits.PEIE = 1; //Habilita las interrupciones externas perifericas
    return;}

void SetupBoton(void)
{
    INTCON2bits.INTEDG1 = 1;
    INTCON2bits.RBPU = 0;
    INTCON3bits.INT1IP = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT1IF = 0;
   
return;}

void H_ISR(void) 
{
   
    if (INT1IF){
        INT1IF=0;
        BTG(LATC,2);
    }
return;}

void Setup(void)
{
    SetupOscilador();
    Setupports();
    Setupint();
    SetupBoton();
return;}





















