#include "config.h"

void main(){

        ANSEL = ANSELH = 0;
        TRISB = 0;
        PORTB = 0;
        C1ON = 0;
        C2ON = 0;
    
    while(1) {
 
        PORTB = 0xFF;
        __delay_ms(250);
        PORTB = 0x00;
        __delay_ms(250);
        
    }

}