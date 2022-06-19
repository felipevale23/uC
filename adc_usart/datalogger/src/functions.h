#include "I2C_LCD.h"

int temp, LDR, pot;
extern char txt1[];
extern char txt2[];

void init()
{
  temp = LDR = pot = 0;
  I2C1_Init(100000); // initialize I2C communication
  I2C_Lcd_Init();

  I2C_Lcd_Cmd(_LCD_CLEAR);
  I2C_Lcd_Out(1, 1, txt1);
  delay_ms(500);
  I2C_Lcd_Out(2, 5, txt2); // Escreve texto na segunda fila
  delay_ms(1000);
  I2C_Lcd_Cmd(_LCD_DISPLAY_ON);
  I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
  I2C_Lcd_Cmd(_LCD_CLEAR);
}

void showDisplay()
{
  I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
  I2C_Lcd_Out(1, 1, txt1);
  I2C_Lcd_Chr(2, 5, 'Temp');
  I2C_Lcd_Chr_Cp(temp);
  I2C_Lcd_Chr_Cp('|');
  I2C_Lcd_Chr_cp('LDR');
  I2C_Lcd_Chr_Cp(LDR + 'V');
  I2C_Lcd_Chr_Cp('|');
  I2C_Lcd_Chr_Cp('POT');
  I2C_Lcd_Chr_Cp(pot + 'V');
}