extern int i;
extern int j;
extern int aux;
extern int aux2;
extern int count;
extern int info[];
extern unsigned char seg_display[];
extern unsigned char pos[];
extern unsigned char erro[];

void showDisplay(int aux){

    if (aux == 0){
     
        for (i = 0; i < 4; i++){

            PORTD = pos[i];
            PORTB = seg_display[info[i]];
            __delay_ms(1);
            PORTD = 0;

        }
     
    }else{
     
        for (i = 0; i < 4; i++){

            PORTD = pos[i];
            PORTB = erro[i];
            __delay_ms(1);
            PORTD = 0;

        }
   
    }

}

void clear(){

    info[3] = info[2] = info[1] = info[0] = 0;
    aux2 = 0;
    aux = 0;
    count = 0;
    i = 0;
}

int isRight(int a, int b, int c, int d){

    if (a == 4 && b == 9 && c == 6 && d == 10){
    
        return 1;

    }else{

        return 0;

    }

}

void init(){

    ANSEL = 0;
    ANSELH = 0;
    TRISD = 0;
    TRISB = 0;
    TRISC = 1;
    PORTD = 0;
    PORTB = 0;
    PORTC = 0;
    count = 0;
    j = 0;

}