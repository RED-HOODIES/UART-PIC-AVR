#include <xc.h>
#include "Setup.h"


void SetupOscilador(void)
{
   // RCCTRL= 0x00;
return;}

void Setupports(void)
{
    //DDRB = 0b00001111; //Configura pines PB0,PB1, PB2 y PB3 como salida  // o para encender 0b00001000;
    //PORTB |= (1 << PORTB4); //Habilita el pull up del PD5
    //PORTB |= (1 << PORTB5); //Habilita el pull up del PD5
return;}

void Setupint(void)
{
    
    return;}

void SetupADC (void)
{
   // ADMUX = 0b01000000; //Habilita la referencia de 5V ADC  (AVcc)
   // ADCSRA = 0b10000000; //Habilita los ADC sin prescaler
    
    
    return;}


void Setup(void)
{   
    SetupOscilador();
    Setupports();
    Setupint();
    SetupADC();
    
return;}


