// Copyright 2022 felip
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "config.h"
#include "I2C_LCD.h"

// Passando valores de texto para um array de char;
unsigned char txt0[] = " PWW ";
unsigned char txt1[] = "V. 1.0";
unsigned char txt2[] = "Freq.:";
unsigned char txt3[] = "D.C.:";

extern char count;

unsigned char aux0, aux1;
unsigned char dutycycle;
unsigned char clickcounter;
unsigned short frequency;

void init()
{

    I2C1_Init(100000); // initialize I2C communication
    I2C_Lcd_Init();
    I2C_Lcd_Cmd(_LCD_CLEAR);
    I2C_Lcd_Out(1, 1, txt0);
    __delay_ms(500);
    I2C_Lcd_Out(2, 5, txt1); // Escreve texto na segunda fila
    __delay_ms(1000);
    I2C_Lcd_Cmd(_LCD_DISPLAY_ON);
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Cmd(_LCD_CLEAR);
}

void registers()
{

    // Configuração do Registrador INTCON
    GIE = 1;  // Habilitação geral das interrupções
    PEIE = 1; // Habilitação dos periféricos
    INTE = 1; // Habilitação de interrupção externa

    // Configuração do Registrador OPTION_REG
    nRBPU = 1;
    INTEDG = 1; // interrupção externa por borda de subida
    T0CS = 0;
    T0SE = 0;
    PSA = 0;
    OPTION_REGbits.PS = 0b001; // configura timer0 prescaler 1:4
    // OPTION_REG = 0x81;        // configura timer0 prescaler 1:4

    // Configuração do TIMER 0
    TMR0 = 0x06;
    TMR0IE = 1;
    TMR0IF = 0;

    ANSEL = 0;  // Configura os pinos AN analógicos como digitais
    ANSELH = 0; // Configura os pinos AN analógicos como digitais
    C1ON = 0;   // Desabilita os comparadores
    C2ON = 0;   // Desabilita os comparadores

    // Configuração do Registrador PORTs
    TRISA = 0x3F;
    TRISB = 0x01; // Pino 0 da porta B como input
    TRISE = 0x00;
    PORTA = 0;
    PORTB = 0;

    // Zerando variáveis
    clickcounter = 0;
    RA0 = RA1 = RA2 = RE0 = 0;
    INTF = 0;
    T0IF = 0;
    frequency = 0;
}

void setFrequency()
{

    switch (clickcounter)
    {

    case 1:
        frequency = 5000;
        break;

    case 2:
        frequency = 3880;
        break;

    case 3:
        frequency = 2125;
        break;

    case 4:
        frequency = 1166;
        break;

    default:
        break;
    }
}

void setDutyCycle()
{
    if (!RA1)
    {
        aux1 = 1;
    }
    if (RA1 && aux1)
    {

        dutycycle == 100 ? dutycycle = 0 : dutycycle++;
        aux1 = 0;
    }
}

void setCounter()
{

    if (count > 5)
        count = 0;
}

void setPWM()
{

    if (
        ((((dutycycle / 100) * frequency) / 1000) >= count) &&
        ((((((dutycycle / 100) * frequency) % 1000) * 255) / 10) >= TMR0))
    {
        RE0 = 1;
    }
    else
    {
        RE0 = 0;
    }
}

void handleClick()
{

    if (PORTA == 0x01 || PORTA == 0x02)
    {

        aux0 = 1;
        aux1 = PORTA;
    }

    if ((PORTA == 0x03) && (aux0 == 1))

        switch (aux1 & 0x03)
        {
        case 0x02:
            (clickcounter == 4) ? clickcounter = 0 : clickcounter++;
            setFrequency();
            aux0 = aux1 = 0;
            break;

        case 0x01:
            setDutyCycle();
            aux0 = aux1 = 0;
            break;

        default:
            aux0 = aux1 = 0;
            break;
        }
}

void setDisplay()
{
    setCounter();
    handleClick();
    setFrequency();
    setDutyCycle();
    setPWM();
}

void showDisplay()
{

    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Out(1, 1, txt2);
    I2C_Lcd_Chr(1, 8, ((frequency / 10) + *"0"));
    I2C_Lcd_Chr_Cp((frequency % 10) + *"0");
    I2C_Lcd_Chr_Cp((((frequency * 10) % 10) + *"0"));
    I2C_Lcd_Out(2, 1, txt3);
    I2C_Lcd_Chr(2, 7, ((dutycycle / 10) + *"0"));
    I2C_Lcd_Chr_Cp((dutycycle % 10) + *"0");
    I2C_Lcd_Chr_Cp((((dutycycle * 10) % 10) + *"0"));
}