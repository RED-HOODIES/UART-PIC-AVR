/*
 * File:   main.c (PERSONALIZACIÓN CARACTER)
 * 
 * Autores: Oscar David Poblador Parra      20211005116
 *          Juan David Bello Rodriguez      20211005028 
 *          Manuel Alejandro Guio Cardona   20211005061
 * Intritución: Universidad Distrital Francisco José de Caldas
 */

#include <xc.h>
#include "Setup.h"

void SetupOscilador(void)
{
    CLKPR = (1 << CLKPCE);
    // Configura el prescaler a 0 para funcionar a la máxima velocidad
    CLKPR = 0;
return;}

void Setupports(void)
{
    DDRF &= ~(1 << DDF0);
    DDRB |= (1 << DDB0);
    DDRD |= (1 << DDD3);
    DDRD &= ~(1 << DDD2);
return;}

void Setupint(void)
{
    return;}

void SetupADC (void)
{
    ADMUX = 0b01000000; //Habilita la referencia de 5V ADC  (AVcc)
    ADCSRA = 0b10000000; //Habilita los ADC sin prescaler
    
    
    return;}


void Setup(void)
{   
    SetupOscilador();
    Setupports();
    Setupint();
    SetupADC();
    
return;}


