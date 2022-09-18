/*
Microchip MPLAB XC8 C Compiler V2.36
Build date: Jan 27 2022
Part Support Version: 2.36
Copyright 2022 Microchip Technology Inc.
License type: Node Configuration
*/

#include <stdbool.h>
#include "config.h"
#include "functions.h"

int count;
int i,j;
bool val;
int aux;
int aux2;

unsigned char seg_display[] = {0x40,0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x79,0x31,0x31,0x3F};
unsigned char erro[] = {0x3F,0x31,0x31,0x79,};
unsigned char pos[] = {0x80,0x40,0x20,0x10};
int info[] = {0,0,0,0};

/* Prototypes */
void showDisplay(int);
void clear();
int isRight(int, int, int, int);
void init();

/* Código principal */
void main(){

    init();

    while(val == false){

        if(PORTC == 0x00){

            val = false;

           showDisplay(0);

        } else {

            val = true;

        }

    }

    while(val == true){

        showDisplay(j);

        if (PORTC == 0x01){

         aux++;

        }

        if (PORTC == 0x02){

         aux2++;

        }

        if (PORTC == 0x00 && !aux == 0){

           info[0] = info[0] == 10 ? 1 : info[0] + 1;
           aux = 0;

        }

         if (PORTC == 0x00 && !aux2 == 0){

              if(count < 3) {

                    switch (count) {

                        case 0 :

                            info[1] = info[0];
                            aux2 = 0;
                            info[0] = 1;

                        break;

                        case 1 :

                            info[2] = info[1];
                            info[1] = info[0];
                            aux2 = 0;
                            info[0] = 1;

                        break;

                        case 2 :

                            info[3] = info[2];
                            info[2] = info[1];
                            info[1] = info[0];
                            aux2 = 0;
                            info[0] = 1;

                        break;

                    }

               count++;

              } else{

                 if (isRight(info[3],info[2],info[1],info[0]) == 1){
                    
                    clear();

                 }else {
                       
                       j = 1;

                 }


              }


         }


    }
}