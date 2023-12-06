/*
 * File:   main.c (PERSONALIZACIÓN CARACTER)
 * 
 * Autores: Oscar David Poblador Parra      20211005116
 *          Juan David Bello Rodriguez      20211005028 
 *          Manuel Alejandro Guio Cardona   20211005061
 * Intritución: Universidad Distrital Francisco José de Caldas
 */

#include <xc.h>

#define _XTAL_FREQ 16000000
#define BTG(R,b) R^=1<<b
#define SALTO UART_printf("\r") 

void SetupOscilador(void);
void Setupports(void);
void Setupint(void);
void Setup(void);


#ifndef SETUP_H
#define	SETUP_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SETUP_H */



