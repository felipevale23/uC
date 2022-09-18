extern int i,j;
extern int aux0, aux1;
unsigned char seg_display[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBF };
unsigned char erro[] = { 0x3F, 0x31, 0x31, 0x79 };
unsigned char pos[] = { 0x10, 0x20, 0x40, 0x80 };
int info[] = { 10, 10, 10, 10 };

void init(){

    ANSEL = 0;
    ANSELH = 0;
    C1ON = 0;
    C2ON = 0;

    TRISA = 0x03;
    TRISD = 0;
    TRISB = 0;

    PORTA = 0;
    PORTD = 0;
    PORTB = 0;

    i = j = aux0 = aux1 = 0;
    
}

void showDisplay(){

    for (i = 0; i < 4; i++){

        PORTD = ~pos[i];
        PORTB = seg_display[info[i]];
        __delay_us(900);

    }

}

void handleClick(){
    
    if (PORTA == 0x01){

        aux0++;

    }

    if(PORTA == 0x00 && !aux0 == 0){

        info[0] >= 9 ? info[0] = 0 : (info[0] = info[0] + 1);
        aux0 = 0;

    }

    if (PORTA == 0x02){

        aux1++;

    }

    if(PORTA == 0x00 && !aux1 == 0){

        if (!(j >= 4)) {

            info[j+1] = info[0];
            info[0] = 0;
            j++;
            aux1=0;


        } else {

            j = 0;

        }
        
    }       

}