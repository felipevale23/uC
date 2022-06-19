/* Laboratório 03 - Experiência 1 *
Baud Rate = 57,6 Kbps, Fosc = 20MHz*/
#include "config.h"
#include "ADC.h"
#include "I2C_LCD.h"
#include "EUSART.h"
#include "functions.h"
#include "registers.h"

// Definir endereço I2C do Display LCD
char LCD_ADDR = 0x40;

// Lcd constants
char txt1[] = " AD Converter ";
char txt2[] = "V. 1.0";

unsigned char dado;
unsigned char flag;

// --- Rotina de Interrupção ---
void interrupt()
{

} // fim da interrupção

void main()
{

    init();
    registers();

    while (1)
    {
        showDisplay();
    }
}