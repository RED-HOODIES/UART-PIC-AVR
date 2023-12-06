
/*------------------------------------------------------------------------------
                                UART AVR
  ------------------------------------------------------------------------------*/

#include <stdint.h>


// Posiciones de memoria destinadas a la UART

volatile uint8_t * const UCSR1A = (volatile uint8_t *) 0x00C8;
volatile uint8_t * const UCSR1B = (volatile uint8_t *) 0x00C9;
volatile uint8_t * const UCSR1C = (volatile uint8_t *) 0x00CA;
volatile uint8_t * const UBRR1L = (volatile uint8_t *) 0x00CC;
volatile uint8_t * const UBRR1H = (volatile uint8_t *) 0x00CD;
volatile uint8_t * const UDR1 = (volatile uint8_t *) 0x00CE;



/* -----------------------------------------------------------------------------
                            CALCULO BAUD RATE
  ------------------------------------------------------------------------------*/
static uint16_t UART_ubrr(uint32_t cpu_clock_hz, uint32_t baud) {
  return (cpu_clock_hz / (16 * baud)) - 1;
}

/* -----------------------------------------------------------------------------
                              INICIO UART
  ------------------------------------------------------------------------------*/
void UART_init(uint32_t baud)
{
  const uint16_t ubrr = UART_ubrr(16000000, baud); // Frecuencia reloj, Baud  - Calcula BAUD RATE
  
  *UBRR1H = (ubrr >> 8); // Registro baud alto
  *UBRR1L = ubrr & 0xff; // Registro baud bajo
  
  //UCSR1A=(0<<RXC1)|(0<<TXC1)|(0<<UDRE1)|(0<<FE1)|(0<<DOR1)|(0<<UPE1)|(0<<U2X1)|(0<<MPCM1) ;   // Banderas
  *UCSR1A=0x00;
  
  //UCSR1B = (1<<RXCIE1)|(0<<TXCIE1)|(0<<UDRIE1)|(1<<RXEN1)|(1<<TXEN1)|(0<<UCSZ12)|(0<<RXB81)|(0<<TXB81);    // Habilita TX y RX. Indica transmisión 8 bits
  *UCSR1B = 0x98;
  
  //UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|(0<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10)|(0<<UCPOL1); // Indica transmisión 8 bits, 1 bit parada, no pariedad. 
  *UCSR1C = 0x06;
}
/* -----------------------------------------------------------------------------
                                IMPRIMIR TEXTO
  ------------------------------------------------------------------------------*/
void UART_caracter(uint8_t data) {

  while ((*UCSR1A & (1<<5)) == 0);  // Espera al canal de tranmisión esté vacío 
  *UDR1 = data;                     // Cuando el el registro UDR1 está vacio se envia el caracter
}
void UART_printf(const char *text)
{
  const char *ptr = text;
  for (;;) {
    if (*ptr == 0) {                // Mientras el último valor de la cadena sea diferente a el caracter nulo
      break;
    }
    UART_caracter(*ptr);            // Transmite los caracteres de cadena
    ++ptr;                          // incrementa la ubicación de los caracteres en cadena para enviar el siguiente 
  }
}
/* -----------------------------------------------------------------------------
                                LEER TEXTO
  ------------------------------------------------------------------------------*/

unsigned char UART_read(){
	if(*UCSR1A &(1<<7)){			//si el bit7 del registro UCSR0A se ha puesto a 1
		return *UDR1;			//devuelve el dato almacenado en el registro UDR0
	}
	else
	return 0;
}



