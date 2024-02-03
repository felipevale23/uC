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

int i, j, aux0, aux1;

/* Prototypes */
void init();
void showDisplay();
void handleClick();

void main(){

    init();

    while(1){

        handleClick();
        showDisplay();
        

    }

}