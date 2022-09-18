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

//Passando valores de texto para um array de char;
unsigned char txt0[] = " TIMER DIGITAL ";
unsigned char txt1[] = "V. 1.0";
unsigned char txt2[] = "OFF   ";
unsigned char txt3[] = "ON   ";
unsigned char txt4[] = "PAUSE    ";
unsigned char txt5[] = " TIMER ";

extern int count;
unsigned char horas, minutos, segundos;
unsigned char start, aux0, aux1, aux2, aux3, aux4;

void init(){

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
    // Configuração de Interrupção
    GIE=1;
    TMR0IE=1;
    TMR0IF=0;

    //Configuração do TIMER 0
    //OPTION_REGbits.TMR0CS=0; // como temporizador
    nRBPU = 1;
    INTEDG = 0;
    T0CS = 0;
    T0SE=0;   
    PSA=0;      // prescaler
    OPTION_REGbits.PS=0b001;   // 1:4
    //OPTION_REG = 0x81;       // configura timer0 prescaler 1:4 
    TMR0 = 0x06;

    ANSEL = 0;                 // Configura os pinos AN analógicos como digitais
    ANSELH = 0;
    C1ON = 0;
    C2ON = 0;

    TRISA = 0x3F; 
    TRISB = 0x00;
    PORTA = 0;
    PORTB = 0;

    start = aux0 = aux1 = aux2 = aux3 =  aux4 = 0;
    RA0 = RA1 = RA2 = 0;

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

void showDisplay(){

    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Out(1, 1, txt5);
    I2C_Lcd_Chr(2, 5, horas / 10 + *"0");
    I2C_Lcd_Chr_Cp(horas % 10 + *"0");
    I2C_Lcd_Chr_Cp(*":");
    I2C_Lcd_Chr_Cp(minutos / 10 + *"0");
    I2C_Lcd_Chr_Cp(minutos % 10 + *"0");
    I2C_Lcd_Chr_Cp(*":");
    I2C_Lcd_Chr_Cp(segundos / 10 + *"0");
    I2C_Lcd_Chr_Cp(segundos % 10 + *"0");

}

void setCounter(){

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
                start = 0;                    // Desliga temporizador
                RB7 = 0;                      // Desliga LED1
                I2C_Lcd_Out(1, 8, txt2);      // escreve OFF ao final da contagem do tempo
                RB3 = 1;                      // Liga Buzzer por 3s
                __delay_ms(3000);
                RB3 = 0;

            }else{ 

                RB7 = 1;                // Liga LED 1

                if(segundos > 0)
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

void start_pause(){

    if (!RA3)
    {
        aux3 = 1;
    }

    if (RA3 && aux3)
    {
        aux3 = 0;
        start = ~start;
    }

    if(start)
    {

        I2C_Lcd_Out(1, 8, txt3);

    }else{

        I2C_Lcd_Out(1, 8, txt4);

        if(count >= 5000)
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

void clear(){

    if(!RA4)
    {
        aux4 = 1;
    }

    if(RA4 && aux4){
        
        start = aux0 = aux1 = aux2 = aux3 =  aux4 = 0;
        minutos = segundos = horas = 0;
        RA0 = RA1 = RA2 = 0;

    }
 
}

void setDisplay(){

    setCounter();
    setSeconds();
    setMinutes();
    setHours();
    start_pause();
    clear();

}
