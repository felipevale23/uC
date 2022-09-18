#include "I2C_LCD.h"

//Explicitando o endereço I2C do LCD.
unsigned char LCD_ADDR = 0x4E;

//Passando valores de texto para um array de char;
char txt0[] = "SENSOR ULTRASSOM"; 
char txt1[] = "Dist:";
char txt2[] = "LIMITE MAX.     ";
char txt3[] = "LIMITE MIN.     ";
char txt4[] = "LEDs";
char txt5[] = "      v1.0      ";

//Estado do Switch case;
unsigned char switcher;

//Estado das distâncias;
int dist0, dist1;

//Configura os registradores;
void init(){

    ANSEL = ANSELH = 0;
    C1ON = 0;
    C2ON = 0;
    TRISA = 0x03;
    TRISB = 0x00;
    PORTB = 0x00;
    RA0 = 0;
    RA1 = 0;
    RA2 = 0;
    dist1 = 3;
    dist0 = 95;

    I2C1_Init(100000);              // Iniciando comunicação I2C em 100kHz;
    I2C_Lcd_Init();                 // Iniciando o protocolo de comunicação I2C com o Display LCD;
    I2C_Lcd_Out(1, 1, txt0);        // Texto de abertura;
    __delay_ms(500);
    I2C_Lcd_Out(2, 1, txt5);        // Texto de abertura;
    __delay_ms(500);
    I2C_Lcd_Cmd(_LCD_DISPLAY_ON);   // Ligando o Display;
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);   // Desligando o cursor;
    I2C_Lcd_Cmd(_LCD_CLEAR);        // Limpando as linhas e colunas;

}

// Limpar as variváveis;
void clear(){

    PORTB = 0;
    switcher = 0;

}

// Mostra as variváveis no Display;
void showDisplay()
{
    
    I2C_Lcd_Cmd(_LCD_CURSOR_OFF);
    I2C_Lcd_Out(1, 1, txt4);
    I2C_Lcd_Out(2, 1, txt1);
    I2C_Lcd_Chr(2, 6 , *" ");
    I2C_Lcd_Chr(2, 7 , *" ");
    I2C_Lcd_Chr_Cp(dist1 + *"0");
    I2C_Lcd_Chr_Cp(*",");
    I2C_Lcd_Chr_Cp((dist0 / 10) + *"0");
    I2C_Lcd_Chr_Cp((dist0 % 10) + *"0");
    I2C_Lcd_Chr(2, 16 , *"m");

}

// Configura os LEDs de acordo com a distância;
void setLEDs(){

    // Se a distância for maior que 2m;
    if(dist0 > 0 && dist1 > 2){

        I2C_Lcd_Chr(1, 15 , *" ");
        I2C_Lcd_Chr(1, 14 , *" ");
        I2C_Lcd_Chr(1, 13 , *" ");
        I2C_Lcd_Chr(1, 12 , *" ");
        I2C_Lcd_Chr(1, 11 , *" ");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");
        PORTB = 0;

    }

    // Se a distância for menor menor 2m e maior 1,80m;
    if((dist0 == 0 && dist1 == 2) || (dist0 >= 80 && dist1 == 1)){

        PORTB = 0;
        PORTB = 0x01;
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *" ");
        I2C_Lcd_Chr(1, 13 , *" ");
        I2C_Lcd_Chr(1, 12 , *" ");
        I2C_Lcd_Chr(1, 11 , *" ");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");

    }

    // Se a distância for menor menor 1,80m e maior 1,20m;    
    if((dist0 < 80 && dist1 == 1) && (dist0 >= 20 && dist1 == 1)){

        PORTB = 0;
        PORTB = 0x03;
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *"1");
        I2C_Lcd_Chr(1, 13 , *" ");
        I2C_Lcd_Chr(1, 12 , *" ");
        I2C_Lcd_Chr(1, 11 , *" ");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");

    }

    // Se a distância for menor menor 1,20m e maior 0,80m;
    if((dist0 < 20 && dist1 == 1) || (dist0 >= 80 && dist1 == 0)){
        
        PORTB = 0;
        PORTB = 0x07;
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *"1");
        I2C_Lcd_Chr(1, 13 , *"1");
        I2C_Lcd_Chr(1, 12 , *" ");
        I2C_Lcd_Chr(1, 11 , *" ");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");

    }

    // Se a distância for menor menor 0,80m e maior 0,50m;
    if((dist0 < 80 && dist1 == 0) && (dist0 >= 50 && dist1 == 0)){

        PORTB = 0;
        PORTB = 0x0F;
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *"1");
        I2C_Lcd_Chr(1, 13 , *"1");
        I2C_Lcd_Chr(1, 12 , *"1");
        I2C_Lcd_Chr(1, 11 , *" ");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");

    }
    
    // Se a distância for menor menor 0,50m e maior 0,20m;
    if((dist0 < 50 && dist1 == 0) && (dist0 >= 20 && dist1 == 0)){

        PORTB = 0;
        PORTB = 0x1F;
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *"1");
        I2C_Lcd_Chr(1, 13 , *"1");
        I2C_Lcd_Chr(1, 12 , *"1");
        I2C_Lcd_Chr(1, 11 , *"1");
        I2C_Lcd_Chr(1, 10 , *" ");
        I2C_Lcd_Chr(1, 9 , *" ");
        I2C_Lcd_Chr(1, 8 , *" ");

    }
    
    // Se a distância for menor menor 0,20m;
    if((dist0 < 20 && dist1 == 0)){
        I2C_Lcd_Chr(1, 15 , *"1");
        I2C_Lcd_Chr(1, 14 , *"1");
        I2C_Lcd_Chr(1, 13 , *"1");
        I2C_Lcd_Chr(1, 12 , *"1");
        I2C_Lcd_Chr(1, 11 , *"1");
        I2C_Lcd_Chr(1, 10 , *"1");
        I2C_Lcd_Chr(1, 9 , *"1");
        I2C_Lcd_Chr(1, 8 , *"1");
        PORTB = 0xFF;
    }
}

// Configura o display LCD.
void setDisplay()
{
    
    clear();
    PORTB = PORTA;
    switcher = PORTA & 0x03;
    PORTB = switcher;

    switch (switcher)
    {
        case 0x02: //incrementando
            
            if (dist0 >= 99) {

                dist1++;
                dist0 = 0;

            }

            if(dist1 >= 4){

                dist1 = 4;
                dist0 = 0;
                __delay_ms(500);
                RA2 = 1;
                I2C_Lcd_Out(2, 1 , txt2);
                __delay_ms(500);
                RA2 = 0;

            }

            showDisplay();
            clear();

            break;

        case 0x01: //decrementando
            
            if(dist1 >= 4){

                dist1--;
                dist0 = 99;

            } 
            if (dist0 == 0) {

                dist1--;
                dist0 = 99;

            }

            if (dist0 <= 2 && dist1 == 0) {

                dist1 = 0;
                dist0 = 2;
                __delay_ms(500);
                RA2 = 1; // ligar buzzer
                I2C_Lcd_Out(2, 1 , txt3);
                __delay_ms(500);
                RA2 = 0;

            }
            
            showDisplay();
            clear();

            break;
        
        default:

            clear();
            break;
    }

}

void handleClick(){

    //sw0 afasta do sensor
    if (RA0 == 0){
        dist0++;
        setDisplay();
    }

    //sw1 aproxima do sensor
    if (RA1 == 0){ 
        dist0--;
        setDisplay();
    }

}