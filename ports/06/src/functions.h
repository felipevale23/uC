#include "I2C_LCD.h"

unsigned char LCD_ADDR = 0x4E;
unsigned char txt3[] = "PRESSIONOU";
unsigned char txt4[] = "A TECLA";

int aux0;


void init(){

    ANSEL = ANSELH = 0;
    C1ON = 0;
    C2ON = 0;
    TRISA = 0x03;
    RA0 = 0;
    RA1 = 0;
    RA2 = 0;
    aux0 = 0;

    I2C1_Init(100000); // initialize I2C communication
    I2C_Lcd_Init();

    I2C_Lcd_Cmd(_LCD_CLEAR);
    __delay_ms(500);
    __delay_ms(1000);
    I2C_Lcd_Cmd(_LCD_DISPLAY_ON);
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Cmd(_LCD_CLEAR);

}

void showDisplay(char txt1, char txt2)
{
    
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Out(1, 1, txt1);
    __delay_ms(500);
    I2C_Lcd_Out(2, 1, txt2);
    __delay_ms(500);
    

}

void handleClick(){

    if (RA0 == 0 && aux0 == 0){
        aux0++;
    }
    if (RA0 == 1 && aux0 > 0){

       showDisplay(txt3, txt4)
        aux0 = 0;

    }

}