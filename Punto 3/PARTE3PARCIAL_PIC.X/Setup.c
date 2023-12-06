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
    OSCCON=0b01110010;
return;}

void Setupports(void)
{
    ADCON0 = 0b00101001; // Habilita el ADC y selecciona AN1 como entrada
    ADCON1 = 0b00000000; // Configura referencias de voltaje y activa todos los pines como analogicos
    ADCON2 = 0b10001000; // Configura FADCK y velocidad de conversi?n
    
    TRISB1=1;
return;}

void Setupint(void)
{
    
    return;}




void Setup(void)
{
    SetupOscilador();
    Setupports();
    Setupint();
return;}


