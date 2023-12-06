#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS  PORTC6   // Pin RS del LCD conectado al pin 2 (PORTD2)
#define LCD_E   PORTC7    // Pin E del LCD conectado al pin 3 (PORTD3)
#define LCD_D4  4    // Pin D4 del LCD conectado al pin 4 (PORTD4)
#define LCD_D5  5    // Pin D5 del LCD conectado al pin 5 (PORTD5)
#define LCD_D6  6    // Pin D6 del LCD conectado al pin 6 (PORTD6)
#define LCD_D7  7    // Pin D7 del LCD conectado al pin 7 (PORTD7)

void LCD_command(unsigned char cmd) {
    PORTD = (cmd & 0xF0);        // Envía el nibble alto del comando
    PORTC &= ~(1 << LCD_RS);     // RS = 0 (Modo comando)
    PORTC |= (1 << LCD_E);       // Habilita el pin E
    _delay_us(1);
    PORTC &= ~(1 << LCD_E);      // Deshabilita el pin E
    _delay_us(100);

    PORTD = ((cmd << 4) & 0xF0); // Envía el nibble bajo del comando
    PORTC |= (1 << LCD_E);
    _delay_us(1);
    PORTC &= ~(1 << LCD_E);
    _delay_us(100);
}

void LCD_data(unsigned char data) {
    PORTD = (data & 0xF0);        // Envía el nibble alto de los datos
    PORTC |= (1 << LCD_RS);       // RS = 1 (Modo datos)
    PORTC |= (1 << LCD_E);
    _delay_us(1);
    PORTC &= ~(1 << LCD_E);
    _delay_us(100);

    PORTD = ((data << 4) & 0xF0); // Envía el nibble bajo de los datos
    PORTC |= (1 << LCD_E);
    _delay_us(1);
    PORTC &= ~(1 << LCD_E);
    _delay_us(100);
}

void LCD_init() {
    DDRD = 0xFF;  // Configura todo el puerto D como salida
    DDRC =0xFF;
    _delay_ms(15);  // Espera a que el LCD se estabilice después de la alimentación
    LCD_command(0x02);  // Inicialización del LCD (modo de 4 bits)
    LCD_command(0x28);  // 2 líneas, matriz de 5x8 puntos
    LCD_command(0x0C);  // Enciende el LCD, apaga el cursor y el parpadeo
    LCD_command(0x06);  // Desplazamiento automático del cursor hacia la derecha
    LCD_command(0x01);  // Limpia la pantalla
}

void LCD_clear() {
    LCD_command(0x01);  // Limpia la pantalla
}

void LCD_setCursor(uint8_t row, uint8_t col) {
    uint8_t position = 0;
    if (row == 1) {
        position = 0x80 + col;  // Primera línea
    } else if (row == 2) {
        position = 0xC0 + col;  // Segunda línea
    }
    LCD_command(position);
}

void LCD_print(const char *str) {
    while (*str) {
        LCD_data(*str);
        str++;
    }
}

//En está función se puede cambiar el tiempo de cambio
void LCD_scrollText(const char *text) {
    LCD_clear();
    int textLength = 0;
    while (text[textLength] != '\0') {
        textLength++;
    }
    
    for (int i = 0; i <= textLength; i++) {
        // Borra la pantalla antes de escribir el texto
        
        // Calcula la posición de inicio para el desplazamiento
        int startPosition = i;
        
        // Verifica si el texto aún cabe en la pantalla
        if (startPosition + 16 > textLength) {
            startPosition = textLength - 16;
        }
        // Imprime la parte del texto que se verá en la pantalla
        LCD_setCursor(1, 0);
        LCD_print(&text[startPosition]);
        
        // Espera un tiempo antes de desplazar
        _delay_ms(100);
    }
}

