#include "config.h"

void main(){

    unsigned char seg7_display[] = {0xC0,0xF9, 0xA4,0xB0,0x99,0x92, 0x82, 0xF8, 0x80, 0x90};
    int i = 0;

    ANSEL =  ANSELH = 0;
    C1ON = 0;
    C2ON = 0;
    TRISB = 0;
    PORTB = 0;

    while (1){

        for (i=0; i<10; i++)
        {
        PORTB = seg7_display[i];
        __delay_ms(2000);
        } //fim do for

    }


}