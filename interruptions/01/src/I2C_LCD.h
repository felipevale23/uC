#include <xc.h>
#include "I2C.h"

#define _LCD_CLEAR 0x01                // Clear display
#define _LCD_4_BIT_MODE 0x02           // 4bit mode
#define _LCD_DECREMENT_CURSOR 0x04     // Decrement cursor (shift cursor to left)
#define _LCD_INCREMENT_CURSOR 0x06     // Increment cursor (shift cursor to right)
#define _LCD_SHIFT_DISPLAY_LEFT 0x07   // Shift display left
#define _LCD_SHIFT_DISPLAY_RIGHT 0x05  // Shift display right
#define _LCD_SET_FIRST_LINE_8BIT 0x30  // Function Set: 8-bit, 1 Line, 5x7 Dots
#define _LCD_SET_SECOND_LINE_8BIT 0x38 // Function Set: 8-bit, 2 Line, 5x7 Dots
#define _LCD_SET_FIRST_LINE_4BIT 0x20  // Function Set: 4-bit, 1 Line, 5x7 Dots
#define _LCD_SET_SECOND_LINE_4BIT 0x28 // Function Set: 4-bit, 2 Line, 5x7 Dots
#define _LCD_TURN_OFF 0x08             // Display Off and Cursor Off
#define _LCD_TURN_ON 0x0E              // Display On and Cursor On
#define _LCD_DISPLAY_ON 0xC0            // Turn on cursor
#define _LCD_CURSOR_ON 0x0E            // Turn on cursor
#define _LCD_CURSOR_OFF 0x0C           // Turn off cursor
#define _LCD_BLINK_CURSOR_ON 0x0F      // Blink cursor on
#define _LCD_SHIFT_LEFT 0x18           // Shift display left without changing display data RAM
#define _LCD_SHIFT_RIGHT 0x1E          // Shift display right without changing display data RAM
#define _LCD_MOVE_CURSOR_LEFT 0x10     // Move cursor left without changing display data RAM
#define _LCD_MOVE_CURSOR_RIGHT 0x14    // Move cursor right without changing display data RAM
#define _LCD_CURSOR_HOME 0x80          // Move cursor to the 1st row
#define _LCD_SECOND_ROW 0xC0           // Move cursor to the 2nd row
#define _LCD_UNDERLINE_ON 0x0E         // Underline cursor on

// LCD Definitions
extern char LCD_ADDR; // char Lcd_I2C_address = 0x40; //A0 - 0, A1 - 0, A2 - 0

void I2C1_Start();
void I2C1_Stop();

// Enviar um comando para Lcd_I2C-PCF8574
void I2C_Lcd_Cmd(char out_char)
{

    char I2C_byte;

    I2C_byte = out_char & 0xF0;

    I2C1_Start();
    I2C1_Write(LCD_ADDR);

    // Configurando o modo comando
    I2C_byte = I2C_byte ^ 0x04;
 
    I2C1_Write(I2C_byte);
    I2C_byte = I2C_byte & 0xF0;
    I2C1_Write(I2C_byte);

    I2C_byte = (out_char << 4) & 0xF0;
    
    // Configurando o modo comando
    I2C_byte = I2C_byte ^ 0x04;

    I2C1_Write(I2C_byte);
    I2C_byte = I2C_byte & 0xF0;

    // Enviando os Comandos
    I2C1_Write(I2C_byte);
    I2C1_Stop();

    __delay_ms(10);
}

// Inicializa o Lcd_I2C-PIC
void I2C_Lcd_Init()
{

    __delay_ms(50);
    I2C1_Start();

    // Enviando os Comandos
    I2C_Lcd_Cmd(_LCD_4_BIT_MODE);
    __delay_ms(10);

    I2C_Lcd_Cmd(_LCD_SET_SECOND_LINE_4BIT);
    __delay_ms(10);

    I2C_Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
    __delay_ms(10);

    I2C_Lcd_Cmd(_LCD_INCREMENT_CURSOR);
    __delay_ms(10);

    I2C_Lcd_Cmd(_LCD_CLEAR);
    __delay_ms(10);

    I2C_Lcd_Cmd(_LCD_CURSOR_HOME);
    __delay_ms(10);
}

// Enviar um caracter para Lcd_I2C-PCF8574
void I2C_Lcd_Chr_Cp(char out_char)
{
    char byte;

    byte = out_char & 0xF0;

    // Selecionando o dispositivo
    I2C1_Start();
    I2C1_Write(LCD_ADDR);

    // Configurando o modo data
    
    byte = byte ^ 0x05;
    I2C1_Write(byte);
    byte = byte & 0xF0;
    byte =  byte ^ 0x01;
    I2C1_Write(byte);

    byte = (out_char << 4) & 0xF0;

    // Configurando o modo data
    byte = byte ^ 0x05;
    I2C1_Write(byte);
    byte = byte & 0xF0;
    byte =  byte ^ 0x01;
    I2C1_Write(byte);

    // Enviando os dados
    I2C1_Stop();
    __delay_ms(10);
}

// Enviar um texto para o Lcd_I2C-PCF8574
void I2C_Lcd_Out_Cp(char *text)
{
    while (*text)
        I2C_Lcd_Chr_Cp(*text++);
}

// Enviar um caracter para uma linha e uma coluna Lcd_I2C-PCF8574
void I2C_Lcd_Chr(char row, char column, char out_char)
{

    switch (row)
    {

    case 1:
        I2C_Lcd_Cmd(0x80 + (column - 1));
        break;
    case 2:
        I2C_Lcd_Cmd(0xC0 + (column - 1));
        break;
    case 3:
        I2C_Lcd_Cmd(0x94 + (column - 1));
        break;
    case 4:
        I2C_Lcd_Cmd(0xD4 + (column - 1));
        break;
    };

    I2C_Lcd_Chr_Cp(out_char);
}

// Enviar um texto para uma linha e uma coluna Lcd_I2C-PCF8574
void I2C_Lcd_Out(char row, char col, char *text)
{
    while (*text)
        I2C_Lcd_Chr(row, col++, *text++);
}