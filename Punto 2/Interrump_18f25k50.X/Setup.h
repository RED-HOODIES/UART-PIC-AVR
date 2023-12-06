

#define _XTAL_FREQ 16000000
#define BTG(R,b) R^=1<<b

void SetupOscilador(void);
void Setupports(void);
void Setupint(void);
void SetupBoton(void);
void __interrupt(high_priority) H_ISR(void);
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



