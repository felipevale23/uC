#include "config.h"

void main(){

        ANSEL = ANSELH = 0;
        TRISB = 0;
        PORTB = 0;

    while(1){

        PORTB = 0xF0;

    }


}