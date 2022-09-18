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

#include "I2C_LCD.h"

//Explicitando o endereço I2C do LCD.
unsigned char LCD_ADDR = 0x4E;

//Passando uma série de valores hexa para um array de char;
unsigned char arr0[] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
unsigned char arr1[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char arr2[] = {0x81,0x42,0x24,0x18};

//Passando valores de texto para um array de char;
unsigned char txt0[] = "LED Array";
unsigned char txt1[] = "Cont.:";

unsigned char aux0;

int count, i; 

//Configura os registradores;
void init(){

    ANSEL = ANSELH = 0;
    C1ON = 0;
    C2ON = 0;
    TRISA = 0x01;
    TRISB = 0x00;
    PORTB = 0x00;
    count = 0;
    i = 0;
    RA0 = 0;
    RA2 = 0;
    aux0 = 0;

    I2C1_Init(100000); // initialize I2C communication
    I2C_Lcd_Init();
    I2C_Lcd_Cmd(_LCD_DISPLAY_ON);
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Cmd(_LCD_CLEAR);

}

// Máquina de estados para configurar o RA0;
void handleClick(){

    //sw0
    if (RA0 == 0 && aux0 == 0){

        aux0 = 0xFF;

    }
    if (RA0 == 1 && aux0 == 0xFF){

        count == 4 ? count = 1 : count++;
        aux0 = 0;
        
    }

}

// Mostra as variváveis no Display;
void setDisplay(){

    I2C_Lcd_Chr(2, 8 , count + *"0" );

}

// Configura os LEDs de acordo com o contador;
void setLEDs(){

    // Altera o estado de acordo com o estado da variável;
    switch (count)
    {
        // Acende todos os LEDs;
        case 1:

            PORTB = 0xFF;
            break;

        // Percorre o vetor que desloca da esquerda para direita;
        case 2:

            for (i=0;i<8;i++){

                PORTB = 0x00;

                PORTB = arr1[i];
                setDisplay();
                __delay_ms(500);
                handleClick();

                if(count != 2)
                    break;

            }

            break;
        
        // Recupera o valor na PORTB e desloca da direita para esquerda;
        case 3:

            PORTB == 0x01 ? PORTB = 0x80 : 0;

            setDisplay();
            __delay_ms(500);
            handleClick();

            PORTB = PORTB >> 1;

            if(count != 3)
                break;


            break;
        
        // Percorre o vetor que acende os pares 0,7 / 1,6 / 2,5 / 3,4;
        case 4:

            for (int i=0;i<4;i++){

                PORTB = 0x00;

                PORTB = arr2[i];
                setDisplay();
                __delay_ms(500);
                handleClick();

                if(count != 4)
                    break;

            }

            break;
        
        case 5:

            count = 1;
            break;

        default:
            PORTB = 0x00;
            break;
    }

}

// Mostra as variváveis no Display;
void showDisplay()
{
    
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Out(1, 1, txt0);
    I2C_Lcd_Out(2, 1, txt1);
    I2C_Lcd_Chr(2, 6 , *" ");
    I2C_Lcd_Chr(2, 7 , *" ");
    I2C_Lcd_Chr_Cp(count + *"0");

}
