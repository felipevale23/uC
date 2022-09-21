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
#include "LCD.h"

// Passando valores de texto para um array de char;
unsigned char txt0[] = " TIMER DIGITAL ";
unsigned char txt1[] = "V. 1.0";
unsigned char txt2[] = "OFF   ";
unsigned char txt3[] = "ON   ";
unsigned char txt4[] = "PAUSE    ";
unsigned char txt5[] = " TIMER ";
unsigned char txt6[] = "SONECA ZzZ";
unsigned char txt7[] = "ACORDA!!!";

extern int count;
extern unsigned char horas, minutos, segundos;
unsigned char start, aux0, aux1, aux2, aux3, aux4;

void init()
{

    Lcd_Init();

    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String(txt0);
    __delay_ms(3000);
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
    TRISB = 0x00; // Pino 0 da porta B como input

    // Zerando variáveis
    start = aux0 = aux1 = aux2 = aux3 = aux4 = 0;
    RA0 = RA1 = RA2 = 0;
    INTF = 0;
    T0IF = 0;
}

// tecla de ajutes segundos/minutos
void setSeconds()
{
    if (!RA0)
    {
        aux0 = 1;
    }
    if (RA0 && aux0)
    {

        segundos == 59 ? segundos = 0 : segundos++;
        aux0 = 0;
    }
}

// tecla de ajutes minutos
void setMinutes()
{

    if (!RA1)
    {
        aux1 = 1;
    }
    if (RA1 && aux1)
    {

        minutos == 59 ? minutos = 0 : minutos++;
        aux1 = 0;
    }
}

// tecla de troca de minutos_segundos para horas_minutos
void setHours()
{

    if (!RA2)
    {
        aux2 = 1;
    }
    if (RA2 && aux2)
    {

        horas == 59 ? horas = 0 : horas++;
        aux2 = 0;
    }
}

void setBuzzer()
{

    RB6 = 1; // Liga Buzzer por 1,5s
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String(txt7); // escreve ACORDAAA
    __delay_ms(1500);
    RB6 = 0;
}

void showDisplay()
{

    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String(txt5);
    Lcd_Write_Char(horas / 10 + *"0");
    Lcd_Write_Char(horas % 10 + *"0");
    Lcd_Write_Char(minutos / 10 + *"0");
    Lcd_Write_Char(minutos % 10 + *"0");
    Lcd_Write_Char(segundos / 10 + *"0");
    Lcd_Write_Char(segundos % 10 + *"0");
}

void setCounter()
{

    if (count >= 5000)
    {
        count = 0;

        if (start) // Ligado em 1
        {
            if (minutos == 0 && horas == 0 && segundos == 0)
            {
                minutos = 0;
                segundos = 0;
                horas = 0;
                start = 0; // Desliga temporizador
                RB7 = 0;   // Desliga LED1
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String(txt2); // escreve OFF ao final da contagem do tempo
                setBuzzer();
            }
            else
            {

                RB7 = 1; // Liga LED 1

                if (segundos > 0)
                    segundos--;

                if (segundos == 0 && minutos == 0 && horas > 0)
                {
                    segundos = 59;
                    minutos = 59;
                    horas--;
                }

                if (segundos == 0 && minutos > 0)
                {
                    segundos = 59;
                    minutos--;
                }
            }
        }
    }
}

void start_pause()
{

    if (!RA3)
    {
        aux3 = 1;
    }

    if (RA3 && aux3)
    {
        aux3 = 0;
        start = ~start;
    }

    if (start)
    {

        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(txt3);
    }
    else
    {

        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(txt4);

        if (count >= 5000)
        {
            RB7 = 1;
            count = 0;
        }
        else
        {
            RB7 = 0;
        }
    }
}

void clear()
{

    if (!RA4)
    {
        aux4 = 1;
    }

    if (RA4 && aux4)
    {

        start = aux0 = aux1 = aux2 = aux3 = aux4 = 0;
        minutos = segundos = horas = 0;
        RA0 = RA1 = RA2 = 0;
    }
}

void setDisplay()
{

    setCounter();
    setSeconds();
    setMinutes();
    setHours();
    start_pause();
    clear();
}
